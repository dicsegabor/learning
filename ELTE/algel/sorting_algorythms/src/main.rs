use compare::{natural, Compare};
use std::cmp::Ordering::{Greater, Less};

fn main() {
    let mut numbers = [4, 65, 2, -31, 0, 99, 2, 83, 782, 1];
    println!("Before: {:?}", numbers);
    selection_sort(&mut numbers, Less);
    println!("After: {:?}", numbers);
}

pub fn bubble_sort<T: Ord>(arr: &mut [T], ord: std::cmp::Ordering) {
    let cmp = natural();
    for i in 0..arr.len() {
        for j in 0..arr.len() - 1 - i {
            if cmp.compare(&arr[j], &arr[j + 1]) == ord {
                arr.swap(j, j + 1);
            }
        }
    }
}

pub fn selection_sort<T: Ord>(arr: &mut [T], ord: std::cmp::Ordering) {
    let (mut comparation_c, mut swap_c) = (0, 0);
    let len = arr.len();
    let cmp = natural();
    for left in 0..len {
        let mut actual = left;
        for right in (left + 1)..len {
            if cmp.compare(&arr[right], &arr[actual]) == ord {
                actual = right;
            }
            comparation_c += 1;
        }
        arr.swap(actual, left);
        swap_c += 1;
    }
    println!("Comparation count: {comparation_c}");
    println!("Swap count: {swap_c}");
}
