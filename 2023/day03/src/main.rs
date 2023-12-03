use std::collections::HashMap;
use std::fs::File;
use std::io::{self, BufRead};

fn solve() -> Result<(), Box<dyn std::error::Error>> {
    let file = File::open("input")?;
    let reader = io::BufReader::new(file);
    // (row, col): num
    let mut num_hash: HashMap<(i32, i32), u32> = HashMap::new();
    let mut symbol_locations: Vec<(i32, i32, char)> = vec![];
    let mut row = 0;
    let mut col = 0;

    // create hashmap of number locations
    for line in reader.lines() {
        let mut num_str = String::from("");
        let mut num_cols: Vec<i32> = vec![]; // columns that belong to the number
        for c in line.unwrap().chars() {
            if c.is_digit(10) {
                num_str.push(c);
                num_cols.push(col);
            } else {
                if c != '.' {
                    symbol_locations.push((row, col, c));
                }
                if !num_str.is_empty() {
                    for n_c in num_cols.iter() {
                        num_hash.insert((row, *n_c), num_str.parse().unwrap());
                    }
                    num_str = String::from("");
                    num_cols = vec![];
                }
            }
            col += 1;
        }
        if !num_str.is_empty() {
            for n_c in num_cols.iter() {
                num_hash.insert((row, *n_c), num_str.parse().unwrap());
            }
        }
        col = 0;
        row += 1;
    }

    let mut sum: u32 = 0;
    let mut gr: u32 = 0;
    for sl in symbol_locations.iter() {
        let mut prod: u32 = 1;
        let mut adj_count: u8 = 0;

        // add / multiply the found numbers for the symbol
        for r in -1..2 {
            // dont count duplicates in the same row
            let mut last_num = 0;
            for c in -1..2 {
                if let Some(num) = num_hash.get(&(sl.0 + r, sl.1 + c)) {
                    if *num != last_num {
                        last_num = *num;
                        sum += *num;
                        if sl.2 == '*' {
                            adj_count += 1;
                            prod *= *num;
                        }
                    }
                }
            }
        }

        if adj_count == 2 {
            gr += prod;
        }
    }

    println!("result 1: {}", sum);
    println!("result 2: {}", gr);

    Ok(())
}

fn main() {
    match solve() {
        Ok(_) => println!("solve success"),
        Err(e) => println!("could not open file: {}", e.to_string()),
    };
}
