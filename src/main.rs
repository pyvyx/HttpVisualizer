#![allow(non_snake_case)]

fn Request(url: &String) -> Result<String, reqwest::Error>
{
    /*
        http://www.boredapi.com/api/activity
        https://cdn.jsdelivr.net/gh/fawazahmed0/currency-api@1/latest/currencies.json

        match Request("..")
        {
            Ok(response) => println!("{}", response),
            Err(e)  => return println!("Failed to make request: '{}'", e),
        }
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
    let input = Input::new(x, y, wind.width()-2*x-10-btnWidth, btnHeight, "");
    let mut btn = Button::new(wind.width()-btnWidth-x, y, btnWidth, btnHeight, "Get");
    let mut out = MultilineOutput::new(x, 50, wind.width()-2*x, wind.height()-input.height()-30, "");

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
                        Ok(response) => out.set_value(&response),
                        Err(e)  => out.set_value(&format!("Failed to make request: '{}'", e)),
                    }
                }
            }
        }
    }
}