ENTRY(vector_start)
SECTIONS
{
    /DISCARD/ : {
        *(.note.gnu.build-id)
    }

    . = 0x40000000;

    .text :
    {
        . = ALIGN(4);
        *(vector_start)
        *(.text .rodata)
    }

    .data :
    {
        *(.data)
    }

    .bss :
    {
        *(.bss)
    }
}
