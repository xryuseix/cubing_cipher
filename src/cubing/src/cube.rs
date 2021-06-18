use anyhow::{bail, Result};

pub struct CubeOP {
    pub direction: u8,
    pub column: u8,
    pub times: u8,
}

pub struct Cube {
    pub cubing: [u8; 54],
}

impl Cube {
    pub fn new(cubing: [u8; 54]) -> Cube {
        Cube { cubing: cubing }
    }

    pub fn rotate(&mut self, key: &CubeOP) -> Result<(), anyhow::Error> {
        let mut tmp: u8;
        let col = key.column as usize;
        match key.direction {
            0 => {
                for _k in 0..key.times * 3 {
                    tmp = self.cubing[0 + col];
                    self.cubing[0 + col] = self.cubing[3 + col];
                    self.cubing[3 + col] = self.cubing[6 + col];
                    self.cubing[6 + col] = self.cubing[12 + col];
                    self.cubing[12 + col] = self.cubing[24 + col];
                    self.cubing[24 + col] = self.cubing[36 + col];
                    self.cubing[36 + col] = self.cubing[45 + col];
                    self.cubing[45 + col] = self.cubing[48 + col];
                    self.cubing[48 + col] = self.cubing[51 + col];
                    self.cubing[51 + col] = self.cubing[44 - col];
                    self.cubing[44 - col] = self.cubing[32 - col];
                    self.cubing[32 - col] = self.cubing[20 - col];
                    self.cubing[20 - col] = tmp;
                }
                Ok(())
            }
            1 => {
                for _k in 0..key.times * 3 {
                    tmp = self.cubing[9 + 12 * col];
                    for m in 0..11 {
                        self.cubing[9 + 12 * col + m] = self.cubing[10 + 12 * col + m];
                    }
                    self.cubing[20 + 12 * col] = tmp;
                }
                Ok(())
            }
            2 => {
                for _k in 0..key.times * 3 {
                    tmp = self.cubing[6 - 3 * col];
                    self.cubing[6 - 3 * col] = self.cubing[7 - 3 * col];
                    self.cubing[7 - 3 * col] = self.cubing[8 - 3 * col];
                    self.cubing[8 - 3 * col] = self.cubing[15 + col];
                    self.cubing[15 + col] = self.cubing[27 + col];
                    self.cubing[27 + col] = self.cubing[39 + col];
                    self.cubing[39 + col] = self.cubing[47 + 3 * col];
                    self.cubing[47 + 3 * col] = self.cubing[46 + 3 * col];
                    self.cubing[46 + 3 * col] = self.cubing[45 + 3 * col];
                    self.cubing[45 + 3 * col] = self.cubing[35 - col];
                    self.cubing[35 - col] = self.cubing[23 - col];
                    self.cubing[23 - col] = self.cubing[11 - col];
                    self.cubing[11 - col] = tmp;
                }
                Ok(())
            }
            _ => bail!("[ERROR] invalid operation."),
        }
    }

    pub fn print_cube(&self) {
        println!("{:?}", self.cubing);
    }
}

#[cfg(test)]
mod tests {
    use super::*;

    fn get_test_arr() -> [u8; 54] {
        let arr: [u8; 54] = [
            97, 98, 99, 100, 101, 102, 103, 104, 105, 106, 107, 108, 109, 110, 111, 112, 113, 114,
            115, 116, 117, 118, 119, 120, 121, 122, 65, 66, 67, 68, 69, 70, 71, 72, 73, 74, 75, 76,
            77, 78, 79, 80, 81, 82, 83, 84, 85, 86, 87, 88, 89, 90, 33, 63,
        ];
        return arr;
    }

    #[test]
    fn rotate_tate_test() {
        let expect: [u8; 54] = [
            97, 110, 99, 100, 122, 102, 103, 76, 105, 106, 107, 108, 109, 85, 111, 112, 113, 114,
            115, 104, 117, 118, 119, 120, 121, 88, 65, 66, 67, 68, 69, 101, 71, 72, 73, 74, 75, 33,
            77, 78, 79, 80, 81, 98, 83, 84, 82, 86, 87, 70, 89, 90, 116, 63,
        ];
        let mut cube = Cube::new(get_test_arr());
        let key = CubeOP {
            direction: 0,
            column: 1,
            times: 1,
        };
        cube.rotate(&key).unwrap();
        assert_eq!(cube.cubing, expect);
    }
    #[test]
    fn rotate_yoko_test() {
        let expect: [u8; 54] = [
            97, 98, 99, 100, 101, 102, 103, 104, 105, 106, 107, 108, 109, 110, 111, 112, 113, 114,
            115, 116, 117, 121, 122, 65, 66, 67, 68, 69, 70, 71, 118, 119, 120, 72, 73, 74, 75, 76,
            77, 78, 79, 80, 81, 82, 83, 84, 85, 86, 87, 88, 89, 90, 33, 63,
        ];
        let mut cube = Cube::new(get_test_arr());
        let key = CubeOP {
            direction: 1,
            column: 1,
            times: 1,
        };
        cube.rotate(&key).unwrap();
        assert_eq!(cube.cubing, expect);
    }
    #[test]
    fn rotate_soto_test() {
        let expect: [u8; 54] = [
            97, 98, 99, 113, 67, 79, 103, 104, 105, 106, 102, 108, 109, 110, 111, 112, 89, 114,
            115, 116, 117, 118, 101, 120, 121, 122, 65, 66, 88, 68, 69, 70, 71, 72, 100, 74, 75,
            76, 77, 78, 87, 80, 81, 82, 83, 84, 85, 86, 107, 119, 73, 90, 33, 63,
        ];
        let mut cube = Cube::new(get_test_arr());
        let key = CubeOP {
            direction: 2,
            column: 1,
            times: 1,
        };
        cube.rotate(&key).unwrap();
        assert_eq!(cube.cubing, expect);
    }
}
