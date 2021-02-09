# DHPC

Dynamic-history prediction compression (DHPC) is an algorithm from ...  This project is an implementation of that algorithm using the reference arithmetic coding library by ... 

## Run

`
make
`

`
dhpc -c in out
`

### Parameters
- et [1, inf) but won't need to be more than m (or even less)
- ct
- m
- z

If you want to define parameters, you must provide all 4.

Leaving any of the parameters as -1 tells the program to use the default value, which depends on the input text.

`
dhcp -c in out et ct m z
`

`
dhpc -d in out
`

`
dhcp -c in out et ct m z
`