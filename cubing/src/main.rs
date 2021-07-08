// use cubing::cube;
// use cubing::decrypt;
// use cubing::encrypt;
// use cubing::cubingmode;
// use cubing::encode;
// use cubing::key;
use std::env;
use clap::Clap;
use std::path::PathBuf;

#[derive(Clap, Debug)]
#[clap(
    name = env!("CARGO_PKG_NAME"),
    version = env!("CARGO_PKG_VERSION"),
    author = env!("CARGO_PKG_AUTHORS"),
    about= env!("CARGO_PKG_DESCRIPTION")
)]
struct Opts {
    /// encrypt
    #[clap(short, long)]
    encrypt: bool,

    /// decrypt
    #[clap(short, long)]
    decrypt: bool,

    /// generate key
    #[clap(short, long)]
    gen_key: bool,

    /// 変換対象ファイル
    #[clap(name = "FILE")]
    plain_file: Option<PathBuf>,
}
fn main() {Opts::parse();}

#[cfg(test)]
mod tests {
    use cubing::cube;
    use cubing::decrypt;
    use cubing::encode;
    use cubing::encrypt;
    use cubing::key;

    #[test]
    fn encrypt_arr_test() {
        let plain_arr: Vec<u8> = vec![
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
            decrypt::decrypt(encrypt::encrypt(plain_arr.clone(), &key), &key),
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

    #[test]
    fn encrypt_decrypt_random_test() {
        for _ in 0..100 {
            let plain_text = encode::gen_ascii_chars(54);
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
