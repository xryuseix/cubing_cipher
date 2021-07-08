use anyhow::{bail, Result};

/* 型を取得する */
pub fn get_typename<T>(_: T) -> &'static str {
    return std::any::type_name::<T>();
}

/* charをintへ変換 */
pub fn char_to_int(c: char) -> Result<i32, anyhow::Error> {
    let res = c as i32 - '0' as i32;
    match 0 <= res && res < 10 {
        true => Ok(res),
        false => bail!("[ERROR] invalid charctor."),
    }
}

/* 数値をバイナリ配列に変換する */
pub fn u8_to_binary(d: u8) -> Result<Vec<u8>, anyhow::Error> {
    let mut bin = Vec::new();
    for i in (0..8).rev() {
        bin.push((d & (1 << i)) / (1 << i));
    }
    Ok(bin)
}

/* バイナリ配列を数値に変換する */
pub fn binary_to_u8(bin: &Vec<u8>) -> Result<u8, anyhow::Error> {
    let mut d = 0;
    for i in 0..8 {
        d += bin[i] * (1 << (7 - i));
    }
    Ok(d)
}

/* 文字列をバイナリ配列の配列に変換する */
pub fn str_to_binary(s: &str) -> Result<Vec<Vec<u8>>, anyhow::Error> {
    let mut bin = Vec::new();
    let a = &s.as_bytes();
    for c in *a {
        bin.push(u8_to_binary(*c).unwrap());
    }
    Ok(bin)
}

/* バイナリ配列の配列を文字列に変換する */
pub fn binary_to_str(bin: &Vec<Vec<u8>>) -> Result<String, anyhow::Error> {
    let mut s = "".to_string();
    for d in bin {
        s += &((binary_to_u8(d).unwrap() as char).to_string());
    }
    Ok(s)
}

/* 文字列を配列へ変換する */
pub fn str_to_arr(s: String) -> Vec<u8> {
    let mut arr = Vec::new();
    let tmp: Vec<u8> = s.into_bytes();
    for byte in tmp {
        arr.push(byte);
    }
    return arr;
}

/* 配列を文字列へ変換する */
pub fn arr_to_str(arr: Vec<u8>) -> String {
    let mut s = "".to_string();
    for d in arr.iter() {
        // s += &((d as char).to_string());
        s += std::str::from_utf8(&[*d]).unwrap();
    }
    return s;
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn char_to_int_test() {
        assert_eq!(char_to_int('0').unwrap(), 0);
        assert_eq!(char_to_int('1').unwrap(), 1);
        assert_ne!(char_to_int('1').unwrap(), 0);
        assert_eq!(
            get_typename(char_to_int('-')),
            "core::result::Result<i32, anyhow::Error>"
        );
    }

    #[test]
    fn convert_binary_and_str_test() {
        assert_eq!(u8_to_binary(1 as u8).unwrap(), vec![0, 0, 0, 0, 0, 0, 0, 1]);
        assert_eq!(
            u8_to_binary('A' as u8).unwrap(),
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
        assert_eq!(binary_to_u8(&vec![0, 1, 0, 0, 0, 0, 0, 1]).unwrap(), 65);
        assert_eq!(binary_to_u8(&u8_to_binary(65).unwrap()).unwrap(), 65);
        assert_eq!(
            binary_to_u8(&u8_to_binary('A' as u8).unwrap()).unwrap(),
            'A' as u8
        );
        assert_eq!(
            binary_to_str(&vec![
                vec![0, 1, 0, 0, 0, 0, 0, 1],
                vec![0, 1, 0, 0, 0, 0, 1, 0],
                vec![0, 1, 0, 0, 0, 0, 1, 1]
            ])
            .unwrap(),
            "ABC".to_string()
        );
        assert_eq!(
            binary_to_str(&str_to_binary("ABC").unwrap()).unwrap(),
            "ABC".to_string()
        );
    }

    #[test]
    fn str_to_arr_test() {
        let s = "ABC".to_string();
        let expected = vec![65, 66, 67];
        assert_eq!(str_to_arr(s), expected);
    }

    #[test]
    fn arr_to_str_test() {
        let arr: Vec<u8> = vec![65, 66, 67];
        let expected = "ABC".to_string();
        assert_eq!(arr_to_str(arr)[0..3], expected);
    }

    #[test]
    fn convert_arr_and_str_test() {
        let s = "ABC".to_string();
        let expected = "ABC".to_string();
        assert_eq!(arr_to_str(str_to_arr(s)), expected);
    }
}
