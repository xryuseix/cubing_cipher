use anyhow::{bail, Result};

pub struct CubeOP {
    direction: u8,
    column: u8,
    times: u8,
}

pub struct Cube {
    cubing: [u8; 54],
}

impl Cube {
    pub fn new(cubing: [u8; 54]) -> Cube {
        Cube { cubing: cubing }
    }

    pub fn rotate(&mut self, key: CubeOP) -> Result<(), anyhow::Error> {
        let mut tmp: u8;
        let col = (key.column - 1) as usize;
        match key.direction {
            1 => Ok(()),
            2 => {
                for _k in 0..key.times * 3 {
                    tmp = self.cubing[9 + 12 * col];
                    for m in 0..11 {
                        self.cubing[9 + 12 * col + m] = self.cubing[10 + 12 * col + m];
                    }
                    self.cubing[20 + 12 * col] = tmp;
                }
                Ok(())
            }
            3 => Ok(()),
            _ => bail!("[ERROR] invalid operation.")
        }
    }

    pub fn print_cube(&self) {
        println!("{:?}", self.cubing);
    }
}

// struct Cube {
//     char cubing[54];

//     Cube (const char (&str)[54]) {
//         for(int i = 0; i < 54; i++) {
//             cubing[i] = str[i];
//         }
//     }

//     void rotate(const CubeOP &key) {
//         char letter;
//         int col = key.column - 1;
//         if(key.direction == 1) { // 方向 // 縦方向
//             for(int k = 0; k < key.times*3; k++) { // 回数

//                 letter = cubing[0 + col]; // colは転値対象列(0~2)
//                 cubing[0 + col] = cubing[3 + col];
//                 cubing[3 + col] = cubing[6 + col];
//                 cubing[6 + col] = cubing[12 + col];
//                 cubing[12 + col] = cubing[24 + col];
//                 cubing[24 + col] = cubing[36 + col];
//                 cubing[36 + col] = cubing[45 + col];
//                 cubing[45 + col] = cubing[48 + col];
//                 cubing[48 + col] = cubing[51 + col];
//                 cubing[51 + col] = cubing[44 - col];
//                 cubing[44 - col] = cubing[32 - col];
//                 cubing[32 - col] = cubing[20 - col];
//                 cubing[20 - col] = letter;

//             }
//         } else if(key.direction == 2){ // 横方向
//             for(int k = 0; k < key.times*3; k++) { // 回数
//                 letter = cubing[9 + 12*col];
//                 for(int m = 0; m < 11; m++) {
//                     cubing[9 + 12*col + m] = cubing[10 + 12*col + m];
//                 }
//                 cubing[20 + 12*col] = letter;
//             }
//         } else if(key.direction == 3) { // 回転方向
//             for(int k = 0; k < key.times*3; k++) { // 回数
//                 letter = cubing[6 - 3*col];
//                 cubing[6 - 3*col] = cubing[7 - 3*col];
//                 cubing[7 - 3*col] = cubing[8 - 3*col];
//                 cubing[8 - 3*col] = cubing[15 + col];
//                 cubing[15 + col] = cubing[27 + col];
//                 cubing[27 + col] = cubing[39 + col];
//                 cubing[39 + col] = cubing[47 + 3*col];
//                 cubing[47 + 3*col] = cubing[46 + 3*col];
//                 cubing[46 + 3*col] = cubing[45 + 3*col];
//                 cubing[45 + 3*col] = cubing[35 - col];
//                 cubing[35 - col] = cubing[23 - col];
//                 cubing[23 - col] = cubing[11 - col];
//                 cubing[11 - col] = letter;
//             }
//         }
//     }

//     bool equals (const Cube& a) const {
//         bool equal = true;
//         for(int i = 0; i < 54; i++) {
//             if(cubing[i] != a.cubing[i]) {
//                 equal = false;
//                 break;
//             }
//         }
//         return equal;
//     }

//     void print() const {
//         for(int i = 0; i < 54; i++) {
//             printf("%c", cubing[i]);
//         }
//         printf("\n");
//     }
// };
