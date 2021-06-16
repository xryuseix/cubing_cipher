use anyhow::{bail, Result};

/* 型を取得する */
pub fn get_typename<T>(_: T) -> &'static str {
    return std::any::type_name::<T>();
}

/* 多分使わん */
pub fn char_to_binary(c: char) -> Result<i32, anyhow::Error> {
    let res = c as i32 - '0' as i32;
    match 0 <= res && res < 10 {
        true => Ok(res),
        false => bail!("[ERROR] invalid charctor."),
    }
}

/* 数値をバイナリ配列に変換する */
pub fn u8_to_binary(d: &u8) -> Result<Vec<u8>, anyhow::Error> {
    let mut bin = Vec::new();
    for i in (0..8).rev() {
        bin.push((d & (1 << i)) / (1 << i));
    }
    Ok(bin)
}

/* 文字列をバイナリ配列の配列に変換する */
pub fn str_to_binary(s: &str) -> Result<Vec<Vec<u8>>, anyhow::Error> {
    let mut bin = Vec::new();
    let a = &s.as_bytes();
    for c in *a {
        bin.push(u8_to_binary(c).unwrap());
    }
    println!("{:?}", bin);
    Ok(bin)
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn to_binary_test() {
        assert_eq!(
            u8_to_binary(&(1 as u8)).unwrap(),
            vec![0, 0, 0, 0, 0, 0, 0, 1]
        );
        assert_eq!(
            u8_to_binary(&('A' as u8)).unwrap(),
            vec![0, 1, 0, 0, 0, 0, 0, 1]
        );
        assert_eq!(
            str_to_binary("ABC").unwrap(),
            vec![
                vec![0, 1, 0, 0, 0, 0, 0, 1],
                vec![0, 1, 0, 0, 0, 0, 1, 0],
                vec![0, 1, 0, 0, 0, 0, 1, 1]
            ]
        );
    }
}
