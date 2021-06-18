// use cubing::cube;
// use cubing::decrypt;
// use cubing::encode;
// use cubing::utils;

fn main() {
    let plain_text = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ!?";
    let b: Vec<u8> = plain_text.to_string().into_bytes();
    let mut c: [u8; 54] = [0; 54];
    for i in 0..54 {
        c[i] = b[i];
    }
    println!("{:?}", b);
}
