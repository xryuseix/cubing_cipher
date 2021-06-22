use rand::Rng;

/*
  任意長の平文にパディングを付与して固定長にする
  * @param text 任意長の平文
  * @return 45の倍数長のパディング付与された平文
*/
pub fn padding(mut text: Vec<u8>) -> Vec<u8> {
    if text.len() % 45 != 0 {
        for _ in 0..8 {
            text.push(0);
        }
    }
    let mut rng = rand::thread_rng();
    while text.len() % 45 != 0 {
        text.push(rng.gen_range(0..2));
    }
    text
}

/*
  固定長の平文をブロック単位で分割する
  * @param text 平文
  * @return 45 Byte単位のブロック列
*/
pub fn block_unit_division(mut text: Vec<u8>) -> Vec<Vec<u8>> {
    let mut blocks: Vec<Vec<u8>> = Vec::new();
    for i in (0..text.len() / 45).rev() {
        blocks.push(text.split_off(i * 45));
    }
    blocks.reverse();
    blocks
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn padding_test() {
        let text = vec![0; 20];
        let mut expected = vec![0; 20];
        let zero = vec![0; 8];
        let pad = vec![0; 17];
        expected.extend(&zero);
        expected.extend(&pad);
        assert_eq!(padding(text.clone()).len(), 45);
        assert_eq!(&padding(text.clone())[0..28], &expected[0..28]);
    }

    #[test]
    fn block_unit_division_test() {
        let mut text = Vec::new();
        for i in 0..135 {
            text.push(i);
        }
        let mut expected = Vec::new();
        for i in 0..3 {
            let mut block= Vec::new();
            for j in 0..45 {
                block.push(i*45+j);
            }
            expected.push(block);
        }
        assert_eq!(block_unit_division(text), expected);
    }
}
