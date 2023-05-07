#![allow(non_snake_case)]
use std::ffi::CStr;
use std::os::raw::c_char;
use std::ffi::CString;

fn MakeRequest(url: &str) -> Result<String, reqwest::Error>
{
    println!("Blocking GET request to: '{}'", url);
    let res = reqwest::blocking::get(url)?.text()?;
    return Ok(res);
}

#[no_mangle]
pub extern "C" fn Request(url: *const c_char) -> *const c_char
{
    if url.is_null() { return std::ptr::null(); }
    let cstr = unsafe { CStr::from_ptr(url) };
    let Ok(urlstr) = cstr.to_str() else { return std::ptr::null() };

    match MakeRequest(urlstr)
    {
        Ok(str) =>
        {
            if let Ok(s) = CString::new(str) 
            {
                return s.into_raw();
            }
            else { return std::ptr::null(); }
        }
        Err(e)  =>
        {
            eprintln!("Failed to make request: '{}'", e);
            return std::ptr::null();
        },
    }
}

#[no_mangle]
pub unsafe extern "C" fn FreeRequest(ptr: *const c_char)
{
    if !ptr.is_null()
    {
        let _ = CString::from_raw(ptr as *mut _);
    }
}