#![allow(non_snake_case)]
use std::ffi::CStr;
use std::os::raw::c_char;
use std::ffi::CString;

fn MakeRequest(url: &str) -> Result<String, reqwest::Error>
{
    let res = reqwest::blocking::get(url)?.text()?;
    return Ok(res);
}

fn StringToCString(str: String) -> *const c_char
{
    if let Ok(s) = CString::new(str) 
    {
        return s.into_raw();
    }
    else { return std::ptr::null(); }
}

#[no_mangle]
pub extern "C" fn Request(url: *const c_char) -> *const c_char
{
    if url.is_null() { return std::ptr::null(); }
    let cstr = unsafe { CStr::from_ptr(url) };
    let Ok(urlstr) = cstr.to_str() else { return std::ptr::null() };

    match MakeRequest(urlstr)
    {
        Ok(str) => return StringToCString(str),
        Err(e)  => return StringToCString(format!("Failed to make request: '{}'", e)),
    }
}

#[no_mangle]
pub unsafe extern "C" fn FreeResponse(response: *const c_char)
{
    if !response.is_null()
    {
        let _ = CString::from_raw(response as *mut _);
    }
}