use anyhow::Result;
use clap::Clap;
use cubing::cubingmode;
use cubing::encode;
use cubing::key;
use std::env;
use std::path::PathBuf;
use std::{cmp, fs, io};

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

    /// 鍵ファイル
    #[clap(name = "KEY_FILE")]
    key_file: Option<PathBuf>,
}
fn main() -> Result<()> {
    let opts = Opts::parse();
    if opts.encrypt {
        let plain_text = match opts.plain_file {
            Some(file) => read_file(file, Some("plain_text".to_string())),
            _ => stdin(Some("plain_text".to_string())),
        }?;
        let key = match opts.key_file {
            Some(file) => key::key_convert(read_file(file, Some("key_text".to_string())).unwrap()),
            _ => key::key_generate(100),
        };
        let (cipher_text, mask1, mask2) = cubingmode::encrypt(encode::str_to_arr(plain_text), &key);
        println!(
            "cipher_text: {}",
            encode::arr_to_str(encode::flatten(cipher_text))
        );
        println!("mask1: {}", encode::arr_to_str(encode::flatten(mask1)));
        println!("mask2: {}", encode::arr_to_str(encode::flatten(mask2)));
    }
    Ok(())
}

/**
 * 標準入力読み込み
 * @param desc 入力内容の説明
 * @return 異常終了: エラー
 *         正常終了: 受け取ったの文字列
 */
fn stdin(description: Option<String>) -> Result<String, anyhow::Error> {
    match description {
        Some(desc) => println!("{}: ", desc),
        _ => {}
    }
    let mut input = String::new();
    io::stdin()
        .read_line(&mut input)
        .expect("Failed to read line.");
    input.pop();
    Ok(input)
}

/**
 * ファイルの読み込み
 * @param path ファイルへの絶対パス
 * @return 異常終了: エラー
 *         正常終了: 実行結果の文字列
 */
fn read_file(path: PathBuf, description: Option<String>) -> Result<String, anyhow::Error> {
    let file_content = fs::read_to_string(path)?;
    match description {
        Some(desc) => println!(
            "{}: \n{}",
            desc,
            &file_content[0..cmp::min(100, file_content.len())]
        ),
        _ => {}
    }
    Ok(file_content)
}

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
