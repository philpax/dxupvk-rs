mod bindings;

use std::os::raw::c_void;

use anyhow::Context;
use windows_sys::Win32::Foundation::HINSTANCE;

fn safe_write<T>(address: *mut T, value: T) {
    use windows_sys::Win32::System::Memory::{
        VirtualProtect, PAGE_PROTECTION_FLAGS, PAGE_READWRITE,
    };
    let mut old: PAGE_PROTECTION_FLAGS = 0;
    let size = std::mem::size_of_val(&value) as usize;
    unsafe {
        VirtualProtect(address as *const _, size, PAGE_READWRITE, &mut old);
        *address = value;
        VirtualProtect(address as *const _, size, old, &mut old);
    }
}

// need to keep detours alive for them to not be disabled
static mut DETOURS: Option<Vec<detour::RawDetour>> = None;
fn jc2_direct_hook() -> anyhow::Result<()> {
    use std::collections::HashMap;
    const FUNCTION_TO_ADDRESS: [((&str, &str), usize); 5] = [
        (("dxgi.dll", "CreateDXGIFactory"), 0xC396F6),
        (("d3d9.dll", "D3DPERF_SetOptions"), 0xC396B4),
        (("d3d10.dll", "D3D10CompileShader"), 0xC396D5),
        (("d3dx10_42.dll", "D3DX10CreateDevice"), 0xC39747),
        (("d3dx10_42.dll", "D3DX10GetFeatureLevel1"), 0xC39737),
    ];

    let functions: HashMap<_, _> = bindings::FUNCTIONS_BY_NAME.into_iter().collect();
    let address_to_replacement: Vec<_> = FUNCTION_TO_ADDRESS
        .into_iter()
        .map(|(p, a)| (a as *const (), *functions.get(&p).unwrap()))
        .collect();

    let mut detours = vec![];
    for (address, replacement) in address_to_replacement {
        unsafe {
            let detour = detour::RawDetour::new(address, replacement)?;
            detour.enable()?;
            detours.push(detour);
        }
    }
    unsafe {
        DETOURS = Some(detours);
    }

    // JC2 attempts to call Nvidia-specific device creation if it detects a Nvidia card.
    // We don't want that, so let's change the conditional jump to an unconditional one.
    safe_write(0x9385C7 as *mut _, 0xEBu8);
    // Similarly, disable stereo vision.
    safe_write(0x938FC8 as *mut _, 0xEBu8);

    Ok(())
}

fn load_impl() -> anyhow::Result<()> {
    let exe_filename = std::env::current_exe()?
        .file_name()
        .context("failed to get filename")?
        .to_string_lossy()
        .to_ascii_lowercase();

    if exe_filename == "justcause2.exe" {
        jc2_direct_hook()
    } else {
        panic!("unsupported executable");
    }
}

#[no_mangle]
#[allow(clippy::missing_safety_doc)]
pub unsafe extern "system" fn load(_: *mut u64, _: *mut u64) {
    load_impl().unwrap();
}

#[no_mangle]
#[allow(non_snake_case)]
#[allow(clippy::missing_safety_doc)]
pub unsafe extern "system" fn DllMain(_: HINSTANCE, _: u32, _: *mut c_void) -> bool {
    true
}
