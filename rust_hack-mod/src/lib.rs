#[cfg(test)]
mod tests {
    #[test]
    fn it_works() {
        assert_eq!(2 + 2, 4);
    }
}
#[macro_use]
extern crate chiter;
extern crate kernel32;
extern crate winapi;

#[macro_use]
extern crate lazy_static;
use std::sync::Mutex;
#[macro_use]
extern crate detour;
use std::collections::HashMap;
use std::thread;
use chiter::VTable;
lazy_static! {
    static ref VTABLE_FUNCTION_POINTER_LIST: Mutex<HashMap<&'static str, usize>> =
        Mutex::new(HashMap::new());
}
#[macro_export]
macro_rules! make_debug_hook_function {
    ($name:ident, $returntype:ty) => {
        fn $name() -> $returntype {
            unsafe {
                let fn_addr: usize = *VTABLE_FUNCTION_POINTER_LIST.lock().unwrap().get(stringify!($name)).unwrap();
                dbg!(stringify!($name));
                let result =  chiter::make_fn!(fn_addr,$returntype)();
                dbg!(result);
                return result;
            }
        }
    };
    ($name:ident, $returntype:ty, $($argument:ty : $argName:ident),*) => {
         fn $name($($argName : $argument,)*) -> $returntype {
            unsafe {
                let fn_addr: usize = *VTABLE_FUNCTION_POINTER_LIST.lock().unwrap().get(stringify!($name)).unwrap();
                dbg!((stringify!($name), $($argName,)*));
                let result = chiter::make_fn!(fn_addr,$returntype,($($argument,)*))(($($argName,)*));
                dbg!(result);
                return result;
            }
        }
    };
}

/*
fn add_money(this: i64, amount: i32) -> i64 {
    let fn_addr: usize = *VTABLE_FUNCTION_POINTER_LIST.lock().unwrap().get("add_money").unwrap();
    unsafe {

        let origfunc = chiter::make_fn!(fn_addr, i64, i64, i32);

        origfunc(this, amount);

        println!("ADDING MONEY TO ME: {}", amount);
        println!("{:02x}", fn_addr);
        return 0;
    }
}
*/

#[macro_export]
macro_rules! set_debug_hook {
    ($table:expr,$position:expr, $name:ident) => {
        let result = match $table.hook($position, $name as usize) {
            Ok(addr) => {
                VTABLE_FUNCTION_POINTER_LIST
                    .lock()
                    .unwrap()
                    .insert(stringify!($name), addr);
                format!("Success Adress: {}", addr)
            }
            Err(e) => format!("ERROR HOOKING: {}", e),
        };
        println!("{}", result);
    };
}


fn injected() {
    unsafe {
        winapi::um::consoleapi::AllocConsole();
       { let mut g3family_table = VTable::new(0x1414665A0, 64);

        make_debug_hook_function!(add_money, i64, i64: this, i32: amount);
        make_debug_hook_function!(remove_money, i64, i64: this, u32: amount);
        //+88 int32 Money
        // +120 int32 Influence
        set_debug_hook!(g3family_table, 38, add_money);
        set_debug_hook!(g3family_table, 39, remove_money);
       }

        
        let mut table = VTable::new(0x141563A70  , 25);
        make_debug_hook_function!(name0, i64, i64: a1,char:a2);
        set_debug_hook!(table, 0, name0);
        make_debug_hook_function!(name1, usize, i64: a1);
        set_debug_hook!(table, 1, name1);
        make_debug_hook_function!(name2, i64, i64: ui3Manager);
        set_debug_hook!(table, 2, name2);
        //make_debug_hook_function!(name29, u64, i64: some_ident,i64:some,i64:xyz);
        //set_debug_hook!(table, 29, name29);
        
        /*
        let result = match table.hook(38, add_money as usize) {
            Ok(addr) => {
                VTABLE_FUNCTION_POINTER_LIST.lock().unwrap().insert("add_money", addr);
                format!("Success Adress: {}", addr)
            }
            Err(e) => format!("ERROR HOOKING: {}", e),
        };
        println!("{}", result);
        let result = match table.hook(39, removeMoney as usize) {
            Ok(addr) => {
                VTABLE_FUNCTION_POINTER_LIST.lock().unwrap().insert("removeMoney", addr);
                format!("Success Adress: {}", addr)
            }
            Err(e) => format!("ERROR HOOKING: {}", e),
        };
        println!("{}", result);
        */
    }
    println!("Injected!");
}
make_entrypoint!(injected);
