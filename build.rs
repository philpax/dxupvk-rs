use glob::glob;

fn main() -> anyhow::Result<()> {
    const DEPENDENCIES: &[&str] = &["dxgi", "d3d11", "d3dcompiler", "User32"];
    for dependency in DEPENDENCIES {
        println!("cargo:rustc-link-lib={}", dependency);
    }

    println!("cargo:rerun-if-changed=src-cpp");
    let mut build = cc::Build::new();
    build
        .cpp(true)
        // files
        .files(glob("src-cpp/**/*.cpp")?.filter_map(Result::ok))
        // compiler flags
        .flag("/std:c++17")
        .flag("/wd4100") // unreferenced formal parameter
        .flag("/wd4459") // hides global declaration
        .flag("/wd4267") // possible loss of data
        .flag("/wd5205"); // delete of an abstract class

    let _is_debug = std::env::var("PROFILE") == Ok("debug".to_string());
    let defines = vec![
        "NOMINMAX",
        "_SILENCE_CXX17_ITERATOR_BASE_CLASS_DEPRECATION_WARNING",
    ];
    for define in defines {
        build.define(define, None);
    }

    build.compile("libdxup");

    Ok(())
}
