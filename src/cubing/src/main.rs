use cubing::decrypt;
use cubing::encode;
use cubing::encrypt;
// use cubing::utils;

fn main() {
    println!(
        "{}",
        encode::binary_to_str(&vec![
            vec![0, 1, 0, 0, 0, 0, 0, 1],
            vec![0, 1, 0, 0, 0, 0, 1, 0],
            vec![0, 1, 0, 0, 0, 0, 1, 1]
        ])
        .unwrap()
    );
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn encrypt_test() {
        assert_eq!(encrypt::encrypt(), 1);
    }
    #[test]
    fn decrypt_test() {
        assert_eq!(decrypt::decrypt(), 2);
    }
}
