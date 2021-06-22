use rand::Rng;
use rand::rngs::ThreadRng;

const CHARSET: &[u8] = b"
0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ!\"#$%&()*+-./:;<=>?@[\\]^_`{|}~\n\0\t";

/*
 * ランダム文字を生成する
 * @param rng 乱数発生器
 * @return ランダム文字
*/
fn get_random_char(mut rng: ThreadRng) -> u8 {
    let idx = rng.gen_range(0..CHARSET.len());
    CHARSET[idx] as u8
}

/*
 * 任意長の平文にパディングを付与して固定長にする
 * @param text 任意長の平文
 * @return 45の倍数長のパディング付与された平文
*/
pub fn padding(mut text: Vec<u8>) -> Vec<u8> {
    if text.len() % 45 != 0 {
        text.push(0);
    }
    let rng = rand::thread_rng();
    while text.len() % 45 != 0 {
        text.push(get_random_char(rng.clone()));
    }
    text
}

/*
 * 固定長の平文をブロック単位で分割する
 * @param text 平文
 * @return 45 Byte単位の平文ブロック
*/
pub fn block_unit_division(mut text: Vec<u8>) -> Vec<Vec<u8>> {
    let mut blocks: Vec<Vec<u8>> = Vec::new();
    for i in (0..text.len() / 45).rev() {
        blocks.push(text.split_off(i * 45));
    }
    blocks.reverse();
    blocks
}

/*
 * 1回目のmaskをかける
 * 乱数とのXORをとる
 * @param text 平文ブロック
 * @return maskをかけた平文ブロック
*/
// pub fn mask_1(mut text: Vec<u8>) -> Vec<u8> {

// }

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn padding_test() {
        let text = vec![1; 20];
        let mut expected = vec![1; 20];
        expected.push(0);
        let pad = vec![0; 24];
        expected.extend(&pad);
        assert_eq!(padding(text.clone()).len(), 45);
        assert_eq!(&padding(text.clone())[0..21], &expected[0..21]);
    }

    #[test]
    fn block_unit_division_test() {
        let mut text = Vec::new();
        for i in 0..135 {
            text.push(i);
        }
        let mut expected = Vec::new();
        for i in 0..3 {
            let mut block = Vec::new();
            for j in 0..45 {
                block.push(i * 45 + j);
            }
            expected.push(block);
        }
        assert_eq!(block_unit_division(text), expected);
    }
}
