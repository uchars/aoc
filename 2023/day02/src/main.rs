use std::collections::HashMap;
use std::fs::File;
use std::io::{self, BufRead};

const MAX_RED: u8 = 12;
const MAX_GREEN: u8 = 13;
const MAX_BLUE: u8 = 14;

struct Pull {
    r: u8,
    g: u8,
    b: u8,
    power: u64,
}

/// Returns Pull struct where the r,g,b fields are the
/// max pulled value.
/// field 0 if value nto pulled
fn get_max_pull(line: String) -> Pull {
    let subsets: Vec<&str> = line.split(";").map(|e| e.trim()).collect();
    // [ [COUNT, COLOR_NAME] ]
    let pulls: Vec<(u8, &str)> = subsets
        .into_iter()
        .flat_map(|c| {
            c.split(",").map(|c| {
                let parts: Vec<&str> = c.trim().split(" ").collect();
                let count: u8 = parts[0].parse().unwrap();
                let name = parts[1];
                (count, name)
            })
        })
        .collect();
    let mut max_counts: HashMap<&str, u8> = HashMap::new();

    for p in pulls {
        let max_count = max_counts.entry(p.1).or_insert(0);
        if p.0 > *max_count {
            *max_count = p.0;
        }
    }

    Pull {
        r: max_counts["red"],
        g: max_counts["green"],
        b: max_counts["blue"],
        power: (max_counts["red"] as u64)
            * (max_counts["green"] as u64)
            * (max_counts["blue"] as u64),
    }
}

fn solve() -> Result<(), Box<dyn std::error::Error>> {
    let file = File::open("input")?;
    let reader = io::BufReader::new(file);
    let mut game_id = 1;
    let mut sum = 0;
    let mut p2_sum = 0;

    for line_it in reader.lines() {
        let line = line_it.unwrap().clone();
        // +1 to skip ':'
        let pull_begin_idx = line.chars().position(|c| c == ':').unwrap() + 1;
        let pull_str = &line[pull_begin_idx..];
        let pull = get_max_pull(pull_str.to_string());
        if pull.r <= MAX_RED && pull.g <= MAX_GREEN && pull.b <= MAX_BLUE {
            sum += game_id;
        }
        p2_sum += pull.power;
        game_id += 1;
    }

    println!("result #1: {}", sum);
    println!("result #2: {}", p2_sum);
    Ok(())
}

fn main() {
    match solve() {
        Ok(_) => println!("solve success"),
        Err(e) => println!("could not open file: {}", e.to_string()),
    };
}
