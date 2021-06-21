pub use crate::cube;
use rand::Rng;

pub fn generate(k: usize) -> Vec<cube::CubeOP> {
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

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn generate_test() {
        let key_len = 90;
        let key = generate(key_len);
        assert_eq!(key.len(), key_len);
        for k in key {
            assert!(k.direction <= 2);
            assert!(k.column <= 2);
            assert!(k.times <= 2);
        }
    }
}
