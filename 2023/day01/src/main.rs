use std::fs::File;
use std::io::{self, BufRead};

const ASCII_0: u8 = 0x30;
const ASCII_9: u8 = 0x39;

const DIGITS: [&str; 18] = [
    "one", "two", "three", "four", "five", "six", "seven", "eight", "nine", "1", "2", "3", "4",
    "5", "6", "7", "8", "9",
];

fn str_to_num(digit: &str) -> u8 {
    match digit {
        "one" => 1,
        "two" => 2,
        "three" => 3,
        "four" => 4,
        "five" => 5,
        "six" => 6,
        "seven" => 7,
        "eight" => 8,
        "nine" => 9,
        n => n.parse::<u8>().unwrap(),
    }
}

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

pub fn solve2() {
    let mut result: u64 = 0;
    let file = File::open("input2").unwrap();
    let reader = io::BufReader::new(file);

    for line in reader.lines() {
        let mut f_pos = Option::None;
        let mut f_digit = Option::None;
        let mut l_pos = Option::None;
        let mut l_digit = Option::None;
        for digit in DIGITS {
            if let Some(pos) = line.as_ref().unwrap().find(digit) {
                if pos <= f_pos.unwrap_or(pos) {
                    f_pos = Some(pos);
                    f_digit = Some(digit);
                }
            }
            if let Some(pos) = line.as_ref().unwrap().rfind(digit) {
                if pos >= l_pos.unwrap_or(pos) {
                    l_pos = Some(pos);
                    l_digit = Some(digit);
                }
            }
        }
        let first = f_digit.map(str_to_num).unwrap();
        let last = l_digit.map(str_to_num).unwrap();
        result += (first as u64) * 10 + (last as u64);
    }

    println!("Solution 2: {}", result);
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
    solve2();
}
