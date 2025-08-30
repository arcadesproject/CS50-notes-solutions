# Networks

# Internet

Internetworked set of computers
Early on ARPANET e.g. west coast universities sending universities in 1969

To send data need **routers** computers/servers to route information from one to another

Routers use **TCP/IP** protocol

**IP** for addressing servers in the world. All computers connected to net have IP address #.#.#.# 0-255 used in each thats **IPv4**, 4 clusters of 8 bytes

**IPv6** uses 128 bit instead of 32 - now 8 clusters of 16 bytes and so uses hexadecimal. Sometimes omit 0s with ::

Access points - with lack of IPv4 addresses a home can have one IP but then router assigns different access points. Different with WANs wide-area networks so to scale access points 

Writes source and destination IP. In bits.

version, ihl, type of service, total length, identification, flags, fragment offset, time to live, protocol, headerr checksum, source address, desitnation address, options, padding

Things get broken up into bits / packages and then reassembled

**TCP** to guarantee delivery, know how many packages sent e.g. package 2 of 4

**ports** unique numeric identifier for specific internet service, e.g. 80 for www traffic, but 443 for securely sent https, 25 email, 53 dns :port-number :443

source port, destination port, sequence number, acknowledgment number, data offset etc

**DNS** domain name server, so go to domain name without needing to put in ip address
Has 2 col table of 'Fully Qualified Domain Name' and 'IP Address' so bit like dict

Some servers can cache ipaddress so if change that but same domain name then still might not work as servers are remembering old ip.

**DHCP** gives computer ip when it boots up on network, dynamic host configuratio protocol. Also tell you what DNS, IP address of default gateway (default router)

**HTTP** hypertext transfer protocol, how web browsers and web servers communicate, while HTTPS is secure/encrypted version only can see the ip address but no other info

**URL** uniform resource locator

/path, /file.html, /folder/

**TLD** top level domain e.g. .com- commercial, .gov - government, .org - organization, .co.uk, .us, .jp diff countries (2 chars is country code technically but some countries monetize the use for anyone)

# Keywords

GET, POST, PUT, DELETE
also PATCH etc

Response codes. e.g. 321 moves, 200 ok, 404 not found, 400 bad request, 401 unauthorized, 403 forbidden, 500 server error, 504 unavailabe

curl to get more detail etc

# HTML
<!DOCTYPE html>
<htme lang = "en">
<head>
<title>
<section>
<div> 
<tr>
<td>
<img src=""> (no closing)
<video controls muted>
etc...

html entities e.g. &#169 for copyright

# DOM

What the browser is really doing when you see webpage. How it translates the html/css etc. Loaded into memory, creating nodes with pointers to represenet tree structure and then display.

?q= common for queries etc. in URLs for user input and & for multiple parts

# Regexp

Regular expressions, vital for validating user input
. single character
* zero or more
+ one or more
? 0 or 1
{n} n occurences
{n, m} at least n, at most m
\ to escape for literatl versions of those special chars
etc...

# CSS

**properties** are sets of key value pairs e.g. height: 420px;

## Javascript

function(event) is lambda function or anonymous function, just do this one thing in one place

eventlisteners for user interaction
submit, keyup, keydown, click, focus, drag, load, mousedown, mouseover, mouseup, unload, blur, change and so on

if (input.value) {
    for (word of WORDS) {
        if (word.startsWith(input.value)) {
            html += '<li>${word}</li>;
        }
    }
}