use rand::Rng;

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
}
