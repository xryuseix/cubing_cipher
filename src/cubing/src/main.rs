// use cubing::cube;
// use cubing::decrypt;
// use cubing::encrypt;
// use cubing::encode;
// use cubing::utils;

fn main() {
    let plain_text = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ!?";
    let b: Vec<u8> = plain_text.to_string().into_bytes();
    let mut c: [u8; 54] = [0; 54];
    for i in 0..54 {
        c[i] = b[i];
    }
    println!("{:?}", b);
}

#[cfg(test)]
mod tests {
    use cubing::cube;
    use cubing::decrypt;
    use cubing::encode;
    use cubing::encrypt;

    #[test]
    fn encrypt_arr_test() {
        let plain_arr: [u8; 54] = [
            97, 98, 99, 100, 101, 102, 103, 104, 105, 106, 107, 108, 109, 110, 111, 112, 113, 114,
            115, 116, 117, 118, 119, 120, 121, 122, 65, 66, 67, 68, 69, 70, 71, 72, 73, 74, 75, 76,
            77, 78, 79, 80, 81, 82, 83, 84, 85, 86, 87, 88, 89, 90, 33, 63,
        ];
        let key: [cube::CubeOP; 2] = [
            cube::CubeOP {
                direction: 0,
                column: 1,
                times: 1,
            },
            cube::CubeOP {
                direction: 2,
                column: 2,
                times: 3,
            },
        ];
        assert_eq!(
            decrypt::decrypt(encrypt::encrypt(plain_arr, &key), &key),
            plain_arr
        );
    }

    #[test]
    fn encrypt_decrypt_test() {
        let plain_text = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ!?".to_string();
        let key: [cube::CubeOP; 1] = [cube::CubeOP {
            direction: 0,
            column: 1,
            times: 1,
        }];
        assert_eq!(
            decrypt::decrypt(
                encrypt::encrypt(encode::str_to_arr(plain_text.clone()), &key),
                &key
            ),
            encode::str_to_arr(plain_text.clone())
        );
    }
}
