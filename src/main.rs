#![allow(non_snake_case)]

fn Request(url: &str) -> Result<String, reqwest::Error>
{
    /*
        http://www.boredapi.com/api/activity
        https://cdn.jsdelivr.net/gh/fawazahmed0/currency-api@1/latest/currencies.json
    */
    return Ok(reqwest::blocking::get(url)?.text()?);
}

fn main()
{
    match Request("..")
    {
        Ok(response) => println!("{}", response),
        Err(e)  => return println!("Failed to make request: '{}'", e),
    }
}
