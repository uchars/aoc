use std::fs::File;
use std::io::{self, BufRead};

const ASCII_0: u8 = 0x30;
const ASCII_9: u8 = 0x39;

fn get_num(text: String) -> Option<u64> {
    let mut num: u8 = 0;
    let mut found_first = false;
    let mut tmp_last: Option<u8> = Option::None;
    for c in text.into_bytes() {
        if c >= ASCII_0 && c <= ASCII_9 {
            if !found_first {
                num += c - ASCII_0;
                found_first = true;
            } else {
                tmp_last = Option::from(c - ASCII_0);
            }
        }
    }
    // sanity check
    match tmp_last {
        Some(n) => Option::from(((num as u64) * 10) + (n as u64)),
        None => {
            // this means that last_digit = first_digit
            Option::from(((num as u64) * 10) + (num as u64))
        }
    }
}

fn solve() -> Result<(), Box<dyn std::error::Error>> {
    let file = File::open("input")?;
    let reader = io::BufReader::new(file);
    let mut num: u64 = 0;
    for line in reader.lines() {
        num += match line {
            Ok(l) => get_num(l).unwrap_or(0),
            Err(_) => 0,
        };
    }
    println!("Result is {}", num);
    Ok(())
}

fn main() {
    match solve() {
        Ok(_) => println!("solve success"),
        Err(e) => println!("could not open file: {}", e.to_string()),
    };
}
