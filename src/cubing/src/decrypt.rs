pub use crate::cube;

pub fn decrypt(plain_text: [u8; 54], key: &[cube::CubeOP]) -> [u8; 54] {
    let mut cube = cube::Cube::new(plain_text);
    for k in key.iter().rev() {
        let mut d_key: cube::CubeOP = (*k).clone();
        d_key.times = 4 - d_key.times;
        cube.rotate(&d_key).unwrap();
    }
    return cube.cubing;
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn decrypt_once_test() {
        let plain_arr: [u8; 54] = [
            97, 98, 99, 100, 101, 102, 103, 104, 105, 106, 107, 108, 109, 110, 111, 112, 113, 114,
            115, 116, 117, 118, 119, 120, 121, 122, 65, 66, 67, 68, 69, 70, 71, 72, 73, 74, 75, 76,
            77, 78, 79, 80, 81, 82, 83, 84, 85, 86, 87, 88, 89, 90, 33, 63,
        ];
        let cipher_arr: [u8; 54] = [
            97, 110, 99, 100, 122, 102, 103, 76, 105, 106, 107, 108, 109, 85, 111, 112, 113, 114,
            115, 104, 117, 118, 119, 120, 121, 88, 65, 66, 67, 68, 69, 101, 71, 72, 73, 74, 75, 33,
            77, 78, 79, 80, 81, 98, 83, 84, 82, 86, 87, 70, 89, 90, 116, 63,
        ];
        let key: [cube::CubeOP; 1] = [cube::CubeOP {
            direction: 0,
            column: 1,
            times: 1,
        }];
        assert_eq!(decrypt(cipher_arr, &key), plain_arr);
    }
}
