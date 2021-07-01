// use cubing::cube;
// use cubing::decrypt;
// use cubing::encrypt;
// use cubing::encode;
// use cubing::key;
// use cubing::cubingmode_utils;
// use cubing::cubingmode_enc;
// use cubing::cubingmode_dec;

fn main() {}

#[cfg(test)]
mod tests {
    use cubing::cube;
    use cubing::decrypt;
    use cubing::encode;
    use cubing::encrypt;
    use cubing::key;
    use rand::seq::SliceRandom;

    #[test]
    fn encrypt_arr_test() {
        let plain_arr: [u8; 54] = [
            97, 98, 99, 100, 101, 102, 103, 104, 105, 106, 107, 108, 109, 110, 111, 112, 113, 114,
            115, 116, 117, 118, 119, 120, 121, 122, 65, 66, 67, 68, 69, 70, 71, 72, 73, 74, 75, 76,
            77, 78, 79, 80, 81, 82, 83, 84, 85, 86, 87, 88, 89, 90, 33, 63,
        ];
        let key: Vec<cube::CubeOP> = vec![
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
        let key: Vec<cube::CubeOP> = vec![cube::CubeOP {
            direction: 0,
            column: 1,
            times: 1,
        }];
        assert_eq!(
            encode::arr_to_str(decrypt::decrypt(
                encrypt::encrypt(encode::str_to_arr(plain_text.clone()), &key),
                &key
            )),
            plain_text.clone()
        );
    }

    fn gen_ascii_chars(size: usize) -> String {
        let mut rng = &mut rand::thread_rng();
        const BASE_STR: &str = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789";
        String::from_utf8(
            BASE_STR
                .as_bytes()
                .choose_multiple(&mut rng, size)
                .cloned()
                .collect(),
        )
        .unwrap()
    }
    #[test]
    fn encrypt_decrypt_random_test() {
        for _ in 0..100 {
            let plain_text = gen_ascii_chars(54);
            let key: Vec<cube::CubeOP> = key::key_generate(20);
            assert_eq!(
                encode::arr_to_str(decrypt::decrypt(
                    encrypt::encrypt(encode::str_to_arr(plain_text.clone()), &key),
                    &key
                )),
                plain_text.clone()
            );
        }
    }
}
