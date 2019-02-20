	ifndef	??version
?debug	macro
	endm
$comm	macro	name,dist,size,count
	comm	dist name:BYTE:count*size
	endm
	else
$comm	macro	name,dist,size,count
	comm	dist name[size]:BYTE:count
	endm
	endif
	?debug	S "sys_req.c"
	?debug	C E93151273C097379735F7265712E63
	?debug	C E90018521813433A5C54435C494E434C5544455C646F732E68
	?debug	C E90018521815433A5C54435C494E434C5544455C5F646566732E68
_TEXT	segment byte public 'CODE'
_TEXT	ends
DGROUP	group	_DATA,_BSS
	assume	cs:_TEXT,ds:DGROUP
_DATA	segment word public 'DATA'
d@	label	byte
d@w	label	word
_DATA	ends
_BSS	segment word public 'BSS'
b@	label	byte
b@w	label	word
_BSS	ends
_TEXT	segment byte public 'CODE'
   ;	
   ;	void sys_req(int op_number,int op_type,char *buff_add,int *length)
   ;	
	assume	cs:_TEXT
_sys_req	proc	near
	push	bp
	mov	bp,sp
   ;	
   ;	{
   ;	  geninterrupt(0x60);   /* If all is set up right, this should      */
   ;	
	int	96
   ;	
   ;	}                       /* invoke sys_call() to handle the request. */
   ;	
	pop	bp
	ret	
_sys_req	endp
	?debug	C E9
_TEXT	ends
_DATA	segment word public 'DATA'
s@	label	byte
_DATA	ends
_TEXT	segment byte public 'CODE'
_TEXT	ends
	public	_sys_req
_s@	equ	s@
	end
