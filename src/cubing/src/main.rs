use cubing::cube;
// use cubing::decrypt;
// use cubing::encode;
use cubing::encrypt;
// use cubing::utils;

fn main() {
    let mut arr: [u8; 54] = [0; 54];
    for i in 0..54 {
        arr[i] = i as u8;
    }
    let cube = cube::Cube::new(arr);
    cube.print_cube();
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn encrypt_test() {
        assert_eq!(encrypt::encrypt(), 1);
    }
    // #[test]
    // fn decrypt_test() {
    //     assert_eq!(decrypt::decrypt(), 2);
    // }
}
