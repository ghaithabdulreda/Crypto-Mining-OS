ENTRY(_start);

SECTIONS
{
    _start = 0x12000;
    . = 0x10000;
    .data : {
        *(.data)
    }
}