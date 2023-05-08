#![allow(non_snake_case)]

fn Request(url: &String) -> Result<String, reqwest::Error>
{
    /*
        http://www.boredapi.com/api/activity
        https://cdn.jsdelivr.net/gh/fawazahmed0/currency-api@1/latest/currencies.json
    */
    return Ok(reqwest::blocking::get(url)?.text()?);
}

use fltk::{
    app,
    button::Button,
    enums::Color,
    output::MultilineOutput,
    prelude::*,
    window::Window,
    input::Input,
};

#[derive(Debug, Copy, Clone)]
enum Message
{
    Get,
}

fn main()
{
    let app = app::App::default();
    let mut wind = Window::default().with_label("Http Visualizer").with_size(1020, 750).center_screen();
    wind.set_color(Color::Dark3);
    wind.make_resizable(true);

    let btnWidth = 150;
    let btnHeight = 30;
    let x = 5;
    let y = 10;
    let outHeight = (wind.height() - 3*y - btnHeight) / 2;
    let mut input = Input::new(x, y, wind.width()-2*x-10-btnWidth, btnHeight, "");
    let mut btn = Button::new(wind.width()-btnWidth-x, y, btnWidth, btnHeight, "Get");
    let mut outJson = MultilineOutput::new(x, 50, wind.width()-2*x, outHeight, "");
    let mut outParsed = MultilineOutput::new(x, 50 + outHeight + y, wind.width()-2*x, outHeight, "");

    input.set_color(Color::Dark2);
    outJson.set_color(Color::Dark2);
    outParsed.set_color(Color::Dark2);

    wind.end();
    wind.show();

    let (s, r) = app::channel::<Message>();
    btn.emit(s, Message::Get);

    while app.wait()
    {
        if let Some(msg) = r.recv()
        {
            match msg
            {
                Message::Get =>
                {
                    match Request(&input.value())
                    {
                        Ok(response) =>
                            {
                                outJson.set_value(&response);
                                let jsonRes = serde_json::from_str(&response);
                                if jsonRes.is_err()
                                {
                                    outParsed.set_value(&format!("JSON was not well-formatted: {}", jsonRes.unwrap_err()));
                                }
                                else
                                {
                                    let json: serde_json::Value = jsonRes.unwrap();
                                    let mut content = String::new();
                                    for (key, value) in json.as_object().unwrap()
                                    {
                                        content += &format!("{} = {}\n", key, value);
                                    }
                                    outParsed.set_value(&content);
                                }
                            },
                        Err(e)  => outJson.set_value(&format!("Failed to make request: '{}'", e)),
                    }
                }
            }
        }
    }
}