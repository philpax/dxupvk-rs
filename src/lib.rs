mod bindings;
mod iat;
mod util;

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
        address.write(value);
        VirtualProtect(address as *const _, size, old, &mut old);
    }
}

fn iat_hook() -> anyhow::Result<()> {
    use iat::import_tables;
    use std::collections::{HashMap, HashSet};

    let dlls: HashSet<&str> = HashSet::from_iter(
        bindings::FUNCTIONS_BY_NAME
            .into_iter()
            .map(|((dll, _), ..)| dll),
    );
    let functions_by_name: HashMap<_, _> = bindings::FUNCTIONS_BY_NAME.into_iter().collect();

    for (library_name, functions) in import_tables().filter(|(l, _)| dlls.contains(l.as_str())) {
        for (function_name, ptr_to_function) in functions {
            if let Some(address) = functions_by_name.get(&(&library_name, &function_name)) {
                safe_write(ptr_to_function, *address);
            }
        }
    }

    Ok(())
}

fn load_impl() -> anyhow::Result<()> {
    let exe_filename = std::env::current_exe()?
        .file_name()
        .context("failed to get filename")?
        .to_string_lossy()
        .to_ascii_lowercase();

    if exe_filename == "justcause2.exe" {
        iat_hook()
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
pub unsafe extern "system" fn DllMain(_: HINSTANCE, _: u32, _: *mut ()) -> bool {
    true
}
