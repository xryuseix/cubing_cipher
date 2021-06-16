use cubing::decrypt;
use cubing::encrypt;
use cubing::utils;

fn main() {
    println!("Hello, world!");
    utils::str_to_binary("681328157").unwrap();
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn char_to_binary_test() {
        assert_eq!(utils::char_to_binary('0').unwrap(), 0);
        assert_eq!(utils::char_to_binary('1').unwrap(), 1);
        assert_ne!(utils::char_to_binary('1').unwrap(), 0);
        assert_eq!(
            utils::get_typename(utils::char_to_binary('-')),
            "core::result::Result<i32, anyhow::Error>"
        );
    }

    #[test]
    fn encrypt_test() {
        assert_eq!(encrypt::encrypt(), 1);
    }
    #[test]
    fn decrypt_test() {
        assert_eq!(decrypt::decrypt(), 2);
    }
}
