use cubing::encrypt;
use cubing::decrypt;
use cubing::common;

fn main() {
    println!("Hello, world!");
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
    #[test]
    fn common_test() {
        assert_eq!(common::common(), 0);
    }
}