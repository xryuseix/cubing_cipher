pub use crate::cube;

pub fn decrypt(cipher_text: Vec<u8>, key: &Vec<cube::CubeOP>) -> Vec<u8> {
    let mut cube = cube::Cube::new(cipher_text);
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
    pub use crate::encode;

    #[test]
    fn decrypt_once_test() {
        let plain_arr: Vec<u8> = vec![
            97, 98, 99, 100, 101, 102, 103, 104, 105, 106, 107, 108, 109, 110, 111, 112, 113, 114,
            115, 116, 117, 118, 119, 120, 121, 122, 65, 66, 67, 68, 69, 70, 71, 72, 73, 74, 75, 76,
            77, 78, 79, 80, 81, 82, 83, 84, 85, 86, 87, 88, 89, 90, 33, 63,
        ];
        let cipher_arr: Vec<u8> = vec![
            97, 110, 99, 100, 122, 102, 103, 76, 105, 106, 107, 108, 109, 85, 111, 112, 113, 114,
            115, 104, 117, 118, 119, 120, 121, 88, 65, 66, 67, 68, 69, 101, 71, 72, 73, 74, 75, 33,
            77, 78, 79, 80, 81, 98, 83, 84, 82, 86, 87, 70, 89, 90, 116, 63,
        ];
        let key: Vec<cube::CubeOP> = vec![cube::CubeOP {
            direction: 0,
            column: 1,
            times: 1,
        }];
        assert_eq!(decrypt(cipher_arr, &key), plain_arr);
    }

    #[test]
    fn encrypt_str_once_test() {
        let plain_text1 = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ!?".to_string();
        let cipher_text1 = "ancdzfgLijklmUopqrshuvwxyXABCDEeGHIJK!MNOPQbSTRVWFYZt?".to_string();
        let key1: Vec<cube::CubeOP> = vec![cube::CubeOP {
            direction: 0,
            column: 1,
            times: 1,
        }];
        assert_eq!(
            decrypt(encode::str_to_arr(cipher_text1), &key1),
            encode::str_to_arr(plain_text1)
        );

        let plain_text2 = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ!?".to_string();
        let cipher_text2 = "abcdefghistujklmnopqrvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ!?".to_string();
        let key2: Vec<cube::CubeOP> = vec![cube::CubeOP {
            direction: 1,
            column: 0,
            times: 3,
        }];
        assert_eq!(
            decrypt(encode::str_to_arr(cipher_text2), &key2),
            encode::str_to_arr(plain_text2)
        );
    }

    #[test]
    fn decrypt_test() {
        let plain_text = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ!?".to_string();
        let cipher_text = "abVqzIghp?fujWQmYcMdrvwxyXEBCDAeGHnJKLsNtPoRSTUlkFOZ!i".to_string();
        // TODO: ここどうにかならないのかな
        let key: Vec<cube::CubeOP> = vec![
            cube::CubeOP {
                direction: 1,
                column: 1,
                times: 3,
            },
            cube::CubeOP {
                direction: 2,
                column: 1,
                times: 3,
            },
            cube::CubeOP {
                direction: 0,
                column: 2,
                times: 3,
            },
            cube::CubeOP {
                direction: 1,
                column: 0,
                times: 3,
            },
            cube::CubeOP {
                direction: 0,
                column: 2,
                times: 1,
            },
            cube::CubeOP {
                direction: 2,
                column: 1,
                times: 2,
            },
            cube::CubeOP {
                direction: 1,
                column: 1,
                times: 1,
            },
            cube::CubeOP {
                direction: 1,
                column: 0,
                times: 3,
            },
            cube::CubeOP {
                direction: 1,
                column: 0,
                times: 1,
            },
            cube::CubeOP {
                direction: 0,
                column: 2,
                times: 2,
            },
        ];
        assert_eq!(
            decrypt(encode::str_to_arr(cipher_text), &key),
            encode::str_to_arr(plain_text)
        );
    }
}
