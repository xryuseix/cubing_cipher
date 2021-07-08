pub use crate::cube;
pub use crate::encode;
use rand::Rng;

pub const CHARSET: &[u8;98] = b"0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ!\"#$%&'()*+,-./:;<=>?@[\\]^_`{|}~ \n\0\t";

pub fn key_generate(k: usize) -> Vec<cube::CubeOP> {
    let mut rng = rand::thread_rng();
    let mut key = Vec::new();
    for _ in 0..k {
        key.push(cube::CubeOP {
            direction: rng.gen_range(0..3),
            column: rng.gen_range(0..3),
            times: rng.gen_range(0..3),
        })
    }
    key
}

pub fn mask_generate(k: usize) -> Vec<u8> {
    let mut rng = rand::thread_rng();
    let mut mask = Vec::new();
    for _ in 0..k {
        mask.push(CHARSET[rng.gen_range(0..CHARSET.len())]);
    }
    mask
}

/**
 * String型の鍵をCubeOP型に変換する
 * @param key_text String型の鍵
 * @return CubeOP型の鍵
 */
pub fn key_convert(key_text: String) -> Vec<cube::CubeOP> {
    let mut key = Vec::new();
    for i in 0..key_text.len() {
        if i % 3 != 0 {
            continue;
        }
        let dir = encode::char_to_int(key_text.chars().nth(i).unwrap()).unwrap() as u8;
        let col = encode::char_to_int(key_text.chars().nth(i + 1).unwrap()).unwrap() as u8;
        let time = encode::char_to_int(key_text.chars().nth(i + 2).unwrap()).unwrap() as u8;
        assert!(dir <= 2 && col <= 2 && time <= 2);
        key.push(cube::CubeOP {
            direction: dir,
            column: col,
            times: time,
        })
    }
    key
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn key_generate_test() {
        let key_len = 90;
        let key = key_generate(key_len);
        assert_eq!(key.len(), key_len);
        for k in key {
            assert!(k.direction <= 2);
            assert!(k.column <= 2);
            assert!(k.times <= 2);
        }
    }

    #[test]
    fn mask_generate_test() {
        for _ in 0..10 {
            let mut rng = rand::thread_rng();
            let k = rng.gen_range(0..10000);
            assert_eq!(mask_generate(k).len(), k);
        }
    }
}
