// pub use crate::cube;
// use rand::Rng;

// pub fn generate(k: usize) -> Vec<cube::CubeOP> {
//     let mut rng = rand::thread_rng();
//     let key_vec: Vec<u8> = (0..k*3).map(|_| rng.gen_range(0..3)).collect();
//     let mut key = Vec::new();
//     for k in key_vec {

//     }
// }

// #[cfg(test)]
// mod tests {
//     use super::*;

//     #[test]
//     fn generate_test() {
//         let key_len = 90;
//         let key = generate(key_len);
//         assert_eq!(key.len(), key_len);
//         for i in 0..key_len {
//             assert!(key[i] <= 2);
//         }
//     }
// }
