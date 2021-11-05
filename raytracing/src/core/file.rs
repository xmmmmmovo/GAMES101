use std::fs::File;
use std::io::{Error, ErrorKind, Read, Result, Write};
use std::path::PathBuf;

pub fn read_file(file_path: PathBuf) -> Result<String> {
    let file = read(file_path)?;
    Ok(file)
}

pub fn write_file(data: &str, filename: &str) -> Result<()> {
    write(data, filename)?;
    Ok(())
}

fn read(path: PathBuf) -> Result<String> {
    let mut buf = String::new();
    let mut file = open(path)?;
    file.read_to_string(&mut buf)?;
    if buf.is_empty() {
        Err(Error::new(ErrorKind::NotFound, "input file missing"))
    } else {
        Ok(buf)
    }
}

fn open(path: PathBuf) -> Result<File> {
    let file = File::open(path)?;
    Ok(file)
}

fn write(data: &str, filename: &str) -> Result<()> {
    let mut buf = File::create(filename)?;
    buf.write_all(data.as_bytes())?;
    Ok(())
}

#[cfg(test)]
mod test {
    use std::path::PathBuf;

    #[test]
    fn test_valid_load_csv() {
        let filename = PathBuf::from("");
    }
}
