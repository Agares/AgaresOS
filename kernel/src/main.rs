#![feature(no_std)]
#![feature(lang_items)]
#![feature(asm)]
#![no_std]

#[lang="sized"]
trait Sized {}

#[lang="copy"]
trait Copy {}

#[lang="start"]
#[no_mangle]
pub fn kmain() {
	loop {}
}
