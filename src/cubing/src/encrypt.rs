pub use crate::cube;

pub fn encrypt(plain_text: [u8; 54], key: &[cube::CubeOP]) -> [u8; 54] {
    let mut cube = cube::Cube::new(plain_text);
    for k in key {
        cube.rotate(k).unwrap();
    }
    return cube.cubing;
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn encrypt_once_test() {
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
        assert_eq!(encrypt(plain_arr, &key), cipher_arr);
    }

    #[test]
    fn encrypt_once_test2() {
        // 4回回転させて元に戻す
        let plain_arr: [u8; 54] = [
            97, 98, 99, 100, 101, 102, 103, 104, 105, 106, 107, 108, 109, 110, 111, 112, 113, 114,
            115, 116, 117, 118, 119, 120, 121, 122, 65, 66, 67, 68, 69, 70, 71, 72, 73, 74, 75, 76,
            77, 78, 79, 80, 81, 82, 83, 84, 85, 86, 87, 88, 89, 90, 33, 63,
        ];
        let cipher_arr: [u8; 54] = [
            97, 98, 99, 100, 101, 102, 103, 104, 105, 106, 107, 108, 109, 110, 111, 112, 113, 114,
            115, 116, 117, 118, 119, 120, 121, 122, 65, 66, 67, 68, 69, 70, 71, 72, 73, 74, 75, 76,
            77, 78, 79, 80, 81, 82, 83, 84, 85, 86, 87, 88, 89, 90, 33, 63,
        ];

        let key: [cube::CubeOP; 1] = [cube::CubeOP {
            direction: 0,
            column: 1,
            times: 4,
        }];
        assert_eq!(encrypt(plain_arr, &key), cipher_arr);
    }

    #[test]
    fn encrypt_once_test3() {
        // 1,3回の順で回転させて元に戻す
        let plain_arr: [u8; 54] = [
            97, 98, 99, 100, 101, 102, 103, 104, 105, 106, 107, 108, 109, 110, 111, 112, 113, 114,
            115, 116, 117, 118, 119, 120, 121, 122, 65, 66, 67, 68, 69, 70, 71, 72, 73, 74, 75, 76,
            77, 78, 79, 80, 81, 82, 83, 84, 85, 86, 87, 88, 89, 90, 33, 63,
        ];
        let cipher_arr: [u8; 54] = [
            97, 98, 99, 100, 101, 102, 103, 104, 105, 106, 107, 108, 109, 110, 111, 112, 113, 114,
            115, 116, 117, 118, 119, 120, 121, 122, 65, 66, 67, 68, 69, 70, 71, 72, 73, 74, 75, 76,
            77, 78, 79, 80, 81, 82, 83, 84, 85, 86, 87, 88, 89, 90, 33, 63,
        ];
        let key1: [cube::CubeOP; 1] = [cube::CubeOP {
            direction: 0,
            column: 1,
            times: 1,
        }];
        let encrypted_arr: [u8; 54] = encrypt(plain_arr, &key1);

        let key2: [cube::CubeOP; 1] = [cube::CubeOP {
            direction: 0,
            column: 1,
            times: 3,
        }];
        assert_eq!(encrypt(encrypted_arr, &key2), cipher_arr);
    }

    fn encrypt_str_test_func(
        plain_text: String,
        cipher_text: String,
        key: [cube::CubeOP; 1],
    ) -> bool {
        let mut plain_arr: [u8; 54] = [0; 54];
        let mut cipher_arr: [u8; 54] = [0; 54];
        let tmp: Vec<u8> = plain_text.into_bytes();
        for i in 0..54 {
            plain_arr[i] = tmp[i];
        }
        let tmp: Vec<u8> = cipher_text.into_bytes();
        for i in 0..54 {
            cipher_arr[i] = tmp[i];
        }
        return encrypt(plain_arr, &key) == cipher_arr;
    }
    #[test]
    fn encrypt_str_once_test() {
        let plain_text1 = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ!?".to_string();
        let cipher_text1 = "ancdzfgLijklmUopqrshuvwxyXABCDEeGHIJK!MNOPQbSTRVWFYZt?".to_string();
        let key1: [cube::CubeOP; 1] = [cube::CubeOP {
            direction: 0,
            column: 1,
            times: 1,
        }];
        assert!(encrypt_str_test_func(plain_text1, cipher_text1, key1));

        let plain_text2 = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ!?".to_string();
        let cipher_text2 = "abcdefghistujklmnopqrvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ!?".to_string();
        let key2: [cube::CubeOP; 1] = [cube::CubeOP {
            direction: 1,
            column: 0,
            times: 3,
        }];
        assert!(encrypt_str_test_func(plain_text2, cipher_text2, key2));
    }
    #[test]
    fn encrypt_test() {
        let plain_text = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ!?".to_string();
        let cipher_text = "abVqzIghp?fujWQmYcMdrvwxyXEBCDAeGHnJKLsNtPoRSTUlkFOZ!i".to_string();
        // TODO: ここどうにかならないのかな
        let key: [cube::CubeOP; 10] = [
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
        let mut plain_arr: [u8; 54] = [0; 54];
        let mut cipher_arr: [u8; 54] = [0; 54];
        let tmp: Vec<u8> = plain_text.into_bytes();
        for i in 0..54 {
            plain_arr[i] = tmp[i];
        }
        let tmp: Vec<u8> = cipher_text.into_bytes();
        for i in 0..54 {
            cipher_arr[i] = tmp[i];
        }
        assert_eq!(encrypt(plain_arr, &key), cipher_arr);
    }
}
