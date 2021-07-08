pub use crate::decrypt;
pub use crate::encode;
pub use crate::encrypt;
pub use crate::key;
use rand::rngs::ThreadRng;
use rand::Rng;

/**
 * ランダム文字を生成する
 * @param rng 乱数発生器
 * @return ランダム文字
 */
pub fn get_random_char(mut rng: ThreadRng) -> u8 {
    let idx = rng.gen_range(0..key::CHARSET.len());
    key::CHARSET[idx] as u8
}

/**
 * key::CHARSETから指定した文字のインデックスを取得する
 * @param インデックスを取得したい文字
 * @return インデックス
 */
fn get_charset_index(c: u8) -> u8 {
    key::CHARSET.iter().position(|&r| r == c).unwrap() as u8
}

/**
 * key::CHARSETから指定したインデックスの文字を取得する
 * @param インデックス
 * @return インデックスに対応する文字
 */
fn get_index_charset(idx: u8) -> u8 {
    key::CHARSET[idx as usize] as u8
}

/**
 * 任意長の平文にパディングを付与して固定長にする
 * @param text 任意長の平文
 * @return 45の倍数長のパディング付与された平文
 */
fn padding(mut text: Vec<u8>) -> Vec<u8> {
    if text.len() % 45 != 0 {
        text.push(0);
    }
    let rng = rand::thread_rng();
    while text.len() % 45 != 0 {
        text.push(get_random_char(rng.clone()));
    }
    text
}

/**
 * 固定長の平文をブロック単位で分割する
 * @param text 平文
 * @return 45 Byte単位の平文ブロック
 */
fn block_unit_division(mut text: Vec<u8>) -> Vec<Vec<u8>> {
    let mut blocks: Vec<Vec<u8>> = Vec::new();
    for i in (0..text.len() / 45).rev() {
        blocks.push(text.split_off(i * 45));
    }
    blocks.reverse();
    blocks
}

/**
 * maskをかける
 * @param text 平文ブロック
 * @return maskをかけた平文ブロック
 * @return mask
 */
pub fn masking(text: Vec<u8>) -> (Vec<u8>, Vec<u8>) {
    assert!([5, 45, 54].contains(&text.len()));
    let mut masked_text = Vec::new();
    let mask = key::mask_generate(text.len());
    for i in 0..text.len() {
        masked_text.push(get_index_charset(
            ((get_charset_index(text[i]) as i32 + mask[i] as i32) % key::CHARSET.len() as i32)
                as u8,
        ));
    }
    assert_eq!(masked_text.len(), mask.len());
    (masked_text, mask)
}

/**
 * maskを元に戻す
 * @param masked_text maskをかけた平文ブロック
 * @param mask mask
 * @return 平文ブロック
 */
pub fn unmasking(masked_text: Vec<u8>, mask: Vec<u8>) -> Vec<u8> {
    assert_eq!(masked_text.len(), mask.len());
    let mut text = Vec::new();
    for i in 0..masked_text.len() {
        let mut char_index = get_charset_index(masked_text[i]) as i32 - mask[i] as i32;
        let charset_len = key::CHARSET.len() as i32;
        // char_indexが負数の時は正に持ち上げる
        char_index = (char_index % charset_len + charset_len) % charset_len;
        text.push(get_index_charset(char_index as u8));
    }
    assert_eq!(masked_text.len(), text.len());
    text
}

/**
 * ハッシュの計算
 * @param text ハッシュ化したいベクトル
 * @return ハッシュ化したベクトル
 */
fn calc_hash(text: Vec<u8>) -> Vec<u8> {
    assert_eq!(text.len(), 45);
    let mut hashs = Vec::new();
    for i in 0..5 {
        let mut hash = 0;
        for j in 9 * i..9 * i + 9 {
            hash += text[j] as u8;
            hash %= 26;
        }
        hash = hash % 26 + 97;
        hashs.push(hash);
    }
    assert_eq!(hashs.len(), 5);
    hashs
}

/**
 * エンコード処理
 * ブロックの末尾に色々つける
 * @param text maskをかけた平文ブロック
 * @return エンコードした平文ブロック
 */
fn encode(masked_text: Vec<u8>, text: Vec<u8>, block_num: u8) -> Vec<u8> {
    assert_eq!(masked_text.len(), 45);
    assert_eq!(text.len(), 45);
    let mut encoded_text = calc_hash((&text[0..45]).to_vec());
    encoded_text.push(key::CHARSET[(block_num / 62) as usize]);
    encoded_text.push(key::CHARSET[(block_num % 62) as usize]);
    let rng = rand::thread_rng();
    encoded_text.push(get_random_char(rng.clone()));
    encoded_text.push(get_random_char(rng.clone()));
    encoded_text
}

/**
 * デコード処理
 * エンコード処理でブロックの末尾についた文字を削除する
 * @param encoded_text エンコードされた平文ブロック
 * @return デコードした平文ブロック
 */
fn decode(encoded_text: Vec<u8>, received_hashs: Vec<u8>) -> Vec<u8> {
    assert_eq!(received_hashs.len(), 5);
    assert_eq!(encoded_text.len(), 45);
    let expected_hashs = calc_hash((&encoded_text[0..45]).to_vec());
    assert_eq!(received_hashs, expected_hashs);
    match encoded_text.iter().position(|&r| r == 0) {
        Some(idx) => return (&encoded_text[0..idx]).to_vec(),
        _ => return (&encoded_text[0..45]).to_vec(),
    }
}

/**
 * 平文ブロックをシャッフルする
 * @param blocks 複数の平文ブロック
 * @return シャッフルした平文ブロック
 */
fn shuffle_blocks(mut blocks: Vec<Vec<u8>>) -> Vec<Vec<u8>> {
    let mut rng = rand::thread_rng();
    let mut t = Vec::default();
    for i in (1..blocks.len()).rev() {
        let idx = rng.gen_range(0..i + 1);
        if i != idx {
            std::mem::swap(&mut blocks[idx], &mut t);
            std::mem::swap(&mut blocks[i], &mut t);
            std::mem::swap(&mut blocks[idx], &mut t);
        }
    }
    blocks
}

/**
 * シーケンシャル番号をデコードする
 * @param place_50 ブロック50番目=十の位
 * @param place_51 ブロック51番目=一の位
 * @return シーケンシャル番号
 */
fn decode_sequence(place_50: u8, place_51: u8) -> i32 {
    return get_charset_index(place_50) as i32 * 62 + get_charset_index(place_51) as i32;
}

/**
 * シャッフルされた平文ブロックをソートする
 * @param blocks シャッフルされた複数の平文ブロック
 * @return ソートされた平文ブロック
 */
fn sort_blocks(mut blocks: Vec<Vec<u8>>) -> Vec<Vec<u8>> {
    blocks.sort_by(|x, y| {
        decode_sequence(x[50], x[51])
            .partial_cmp(&decode_sequence(y[50], y[51]))
            .unwrap()
    });
    blocks
}

/**
 * 暗号化
 * @param plain_text 平文
 * @param key 鍵
 * @return 暗号文, mask1, mask2
 */
pub fn encrypt(
    plain_text: Vec<u8>,
    key: &Vec<key::cube::CubeOP>,
) -> (Vec<Vec<u8>>, Vec<Vec<u8>>, Vec<Vec<u8>>) {
    let padded_text = padding(plain_text.clone());
    let plain_blocks = block_unit_division(padded_text.clone());
    println!("plain_blocks: {:?}", plain_blocks);
    let mut encoded_blocks: Vec<Vec<u8>> = Vec::new();
    let mut mask_blocks1: Vec<Vec<u8>> = Vec::new();
    let mut mask_blocks2: Vec<Vec<u8>> = Vec::new();
    
    for (i, block) in plain_blocks.iter().enumerate() {
        let (mut masked_block, mask1) = masking(block.to_vec());
        let encoded_tail = encode(masked_block.clone(), block.to_vec(), i as u8);
        let (mut masked_tail, mask2) = masking((&encoded_tail[0..5]).to_vec());
        masked_block.append(&mut masked_tail);
        masked_block.append(&mut (&encoded_tail[5..9]).to_vec());
        encoded_blocks.push(encrypt::encrypt(masked_block.clone(), key));
        
        assert_eq!(mask1.len(), 45);
        assert_eq!(mask2.len(), 5);
        mask_blocks1.push(mask1);
        mask_blocks2.push(mask2);
    }
    println!("cipher_text1: {:?}", encoded_blocks);

    assert_eq!(encoded_blocks.len(), plain_blocks.len());
    assert_eq!(mask_blocks1.len(), plain_blocks.len());
    assert_eq!(mask_blocks2.len(), plain_blocks.len());
    return (shuffle_blocks(encoded_blocks), mask_blocks1, mask_blocks2);
}

/**
 * 復号
 * @param cipher_text 平文
 * @param mask1 mask1
 * @param mask2 mask2
 * @param key 鍵
 * @return 平文
 */
pub fn decrypt(
    cipher_text: Vec<Vec<u8>>,
    mask1: Vec<Vec<u8>>,
    mask2: Vec<Vec<u8>>,
    key: &Vec<key::cube::CubeOP>,
) -> String {
    println!("cipher_text3: {:?}", cipher_text);
    let mut decrypted_blocks: Vec<Vec<u8>> = Vec::new();
    for block in cipher_text {
        let decrypted_block = decrypt::decrypt(block, key);
        let mut unmasked2_block = (&decrypted_block[0..45]).to_vec();
        println!("unmasked2_block: {:?} ({})", unmasked2_block, unmasked2_block.len());
        println!("decrypted_block: {:?} ({})\n", decrypted_block, decrypted_block.len());
        let sequence = decode_sequence(decrypted_block[50], decrypted_block[51]);
        unmasked2_block.append(&mut unmasking(
            (&decrypted_block[45..50]).to_vec(),
            mask2[sequence as usize].clone(),
        ));
        decrypted_blocks.push(unmasked2_block);
    }
    decrypted_blocks = sort_blocks(decrypted_blocks);
    let mut cipher_text = String::new();
    for (block, mask) in decrypted_blocks.iter().zip(mask1.iter()) {
        let unmasked1_block = unmasking((&block[0..45]).to_vec(), (*mask).clone());
        let decoded_block = decode(unmasked1_block, (&block[45..50]).to_vec());
        cipher_text += &encode::arr_to_str(decoded_block);
    }
    return cipher_text;
}

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

    #[test]
    fn get_charset_index_test() {
        assert_eq!(get_charset_index('0' as u8), 0 as u8);
        assert_eq!(get_charset_index('a' as u8), 10 as u8);
        assert_eq!(get_charset_index('!' as u8), 62 as u8);
    }

    #[test]
    fn encode_test() {
        let mut v = Vec::new();
        for i in 0..45 {
            v.push(i as u8);
        }
        let expected = vec![107, 110, 113, 116, 119, '1' as u8, '3' as u8];
        assert_eq!(encode(v.clone(), v.clone(), 65)[0..7], expected[0..7]);
    }

    #[test]
    fn mask_unmask_test() {
        let mut text = Vec::new();
        let rng = rand::thread_rng();
        for _ in 0..54 {
            text.push(get_random_char(rng.clone()));
        }
        let (masked_text, mask) = masking(text.clone());
        let unmasked_text = unmasking(masked_text, mask);
        assert_eq!(text, unmasked_text);
    }

    #[test]
    fn sort_blocks_test() {
        let vec = vec![0; 54];
        let mut block1 = vec.clone();
        block1[50] = 65;
        block1[51] = 65;
        let mut block2 = vec.clone();
        block2[50] = 66;
        block2[51] = 68;
        let mut block3 = vec.clone();
        block3[50] = 67;
        block3[51] = 67;

        let random_blocks1 = vec![block3.clone(), block2.clone(), block1.clone()];
        let random_blocks2 = vec![block2.clone(), block1.clone(), block3.clone()];
        let random_blocks3 = vec![block1.clone(), block3.clone(), block2.clone()];
        let random_blocks4 = vec![block1.clone(), block2.clone(), block3.clone()];
        let expected = vec![block1.clone(), block2.clone(), block3.clone()];

        assert_eq!(sort_blocks(random_blocks1), expected);
        assert_eq!(sort_blocks(random_blocks2), expected);
        assert_eq!(sort_blocks(random_blocks3), expected);
        assert_eq!(sort_blocks(random_blocks4), expected);
    }

    #[test]
    fn encrypt_decrypt_test() {
        for _ in 0..1 {
            // let text = encode::gen_ascii_chars(46);
            let text = "A".to_string().repeat(46);
            let key = key::key_generate(100);
            let (cipher_text, mask1, mask2) = encrypt(encode::str_to_arr(text.clone()), &key);
            println!("cipher_text2: {:?}", cipher_text);
            let plain_text = decrypt(cipher_text, mask1, mask2, &key);
            assert_eq!(text, plain_text);
        }
    }
}
