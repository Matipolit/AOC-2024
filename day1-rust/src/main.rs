use clap::{Arg, Command};
use std::collections::HashMap;
use std::io::{self, BufRead};

fn main() {
    let matches = Command::new("Parser")
        .version("1.0")
        .about("Day 1 Advent Of Code 2024 implementation")
        .arg(
            Arg::new("part")
                .short('p')
                .long("part")
                .value_parser(["1", "2"])
                .default_value("1")
                .help("Specify the part of the program to run (1 or 2)"),
        )
        .get_matches();

    let part: u32 = matches.get_one::<String>("part").unwrap().parse().unwrap();
    println!("Running part {} of the program", part);

    let stdin = io::stdin();
    let handle = stdin.lock();

    let mut numbers_left: Vec<i32> = Vec::with_capacity(1000);
    let mut numbers_right: Vec<i32> = Vec::with_capacity(1000);

    for line in handle.lines() {
        match line {
            Ok(content) => {
                if content != "" {
                    let left_value = &content[0..5];
                    let right_value = &content[8..13];

                    match (left_value.parse::<i32>(), right_value.parse::<i32>()) {
                        (Ok(left_parsed), Ok(right_parsed)) => {
                            numbers_left.push(left_parsed);
                            numbers_right.push(right_parsed);
                        }
                        _ => {
                            println!("Error: line malformed, could not parse values!");
                        }
                    }
                }
            }
            Err(e) => {
                eprintln!("Error reading line: {}", e);
                break;
            }
        }
    }

    match part {
        1 => {
            numbers_left.sort();
            numbers_right.sort();

            let mut sum = 0;
            numbers_left.iter().enumerate().for_each(|(idx, left_num)| {
                sum += left_num.abs_diff(numbers_right[idx]);
            });

            println!("Sum: {}", sum);
        }
        2 => {
            let mut numbers_map: HashMap<i32, i32> =
                numbers_left.into_iter().map(|num| (num, 0)).collect();

            numbers_right.iter().for_each(|num_right| {
                if let Some(num_count) = numbers_map.get_mut(num_right) {
                    *num_count += 1;
                }
            });
            let mut sum = 0;
            numbers_map.iter().for_each(|(key, val)| {
                sum += key * val;
            });

            println!("Sum: {}", sum);
        }
        _ => {
            panic!("Invalid program part. Only 1 and 2 are availale.")
        }
    }
}
