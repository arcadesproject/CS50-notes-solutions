Certainly. Here's a cleaned-up and structured version of your notes in Markdown format, with added context, improved formatting, and summary explanations at the end of each section. The table of contents links to each topic, and suggested next topics are listed at the end.

---

# Web & Network Fundamentals

## Topics Covered

- [Internet & Networking Basics](#internet--networking-basics)
- [IP, TCP, and Ports](#ip-tcp-and-ports)
- [DNS & DHCP](#dns--dhcp)
- [HTTP, HTTPS, and URLs](#http-https-and-urls)
- [HTTP Methods & Status Codes](#http-methods--status-codes)
- [HTML Basics](#html-basics)
- [DOM (Document Object Model)](#dom-document-object-model)
- [Regular Expressions](#regular-expressions)
- [CSS Fundamentals](#css-fundamentals)
- [JavaScript Essentials](#javascript-essentials)
- [Next Topics to Study](#next-topics-to-study)

---

## Internet & Networking Basics

The internet is a global network of interconnected computers. It began with ARPANET in 1969, connecting universities on the U.S. West Coast.

To send data across networks, devices use **routers**, which direct traffic using the **TCP/IP protocol suite**.

- **IPv4**: 32-bit addressing using four octets (e.g. `192.168.0.1`)
- **IPv6**: 128-bit addressing using eight groups of hexadecimal numbers (e.g. `2001:0db8::1`)
- Data is broken into packets, each containing metadata like source/destination IP, version, length, and more.

**Summary:**  
The internet relies on routers and protocols to transmit data between devices. IP addresses identify devices, and packets ensure efficient delivery.

---

## IP, TCP, and Ports

- **IP (Internet Protocol)**: Handles addressing and routing.
- **TCP (Transmission Control Protocol)**: Ensures reliable delivery of packets, tracking sequence and acknowledgment numbers.
- **Ports**: Identify specific services on a device.

| Port | Service         |
|------|-----------------|
| 80   | HTTP            |
| 443  | HTTPS (secure)  |
| 25   | Email (SMTP)    |
| 53   | DNS             |

TCP headers include fields like source/destination port, sequence number, and checksum.

**Summary:**  
TCP/IP enables reliable communication between devices. Ports distinguish services, allowing multiple applications to run on the same machine.

---

## DNS & DHCP

- **DNS (Domain Name System)**: Translates domain names (e.g. `example.com`) into IP addresses.
- **DHCP (Dynamic Host Configuration Protocol)**: Assigns IP addresses to devices when they connect to a network and provides DNS and gateway info.

DNS servers may cache IP addresses, which can cause issues if a domain’s IP changes but the cache hasn’t updated.

**Summary:**  
DNS makes web navigation user-friendly by resolving names to IPs. DHCP automates network configuration for connected devices.

---

## HTTP, HTTPS, and URLs

- **HTTP (Hypertext Transfer Protocol)**: Defines how browsers and servers communicate.
- **HTTPS**: Secure version of HTTP using encryption.
- **URL (Uniform Resource Locator)**: Specifies the location of a resource on the web.

Example URL structure:  
`https://example.com/folder/file.html`

- **TLD (Top-Level Domain)**: The last part of a domain name (e.g. `.com`, `.org`, `.gov`, `.co.uk`)

**Summary:**  
HTTP and HTTPS govern web communication. URLs identify resources, and TLDs categorize domains by purpose or geography.

---

## HTTP Methods & Status Codes

### Common HTTP Methods

- `GET`: Retrieve data
- `POST`: Submit data
- `PUT`: Replace data
- `DELETE`: Remove data
- `PATCH`: Partially update data

### Common Status Codes

| Code | Meaning             |
|------|---------------------|
| 200  | OK                  |
| 301  | Moved Permanently   |
| 400  | Bad Request         |
| 401  | Unauthorized        |
| 403  | Forbidden           |
| 404  | Not Found           |
| 500  | Internal Server Error |
| 504  | Gateway Timeout     |

Tools like `curl` can be used to inspect HTTP responses.

**Summary:**  
HTTP methods define actions on resources. Status codes indicate the result of those actions, helping diagnose issues.

---

## HTML Basics

HTML (HyperText Markup Language) structures web content.

### Common Tags

```html
<!DOCTYPE html>
<html lang="en">
<head>
  <title>Page Title</title>
</head>
<body>
  <section>
    <div>
      <table>
        <tr>
          <td>Cell</td>
        </tr>
      </table>
      <img src="image.jpg">
      <video controls muted></video>
    </div>
</body>
</html>
```

- HTML entities like `&#169;` represent special characters.

**Summary:**  
HTML defines the structure of web pages using nested tags. It’s the foundation of all web content.

---

## DOM (Document Object Model)

The DOM is the browser’s internal representation of a webpage. It parses HTML/CSS into a tree of nodes, each representing an element.

- Nodes have parent/child relationships.
- JavaScript can manipulate the DOM dynamically.

Query strings in URLs (e.g. `?q=search&lang=en`) pass user input to the server.

**Summary:**  
The DOM enables dynamic interaction with web pages. It’s a live model that reflects and responds to user actions and scripts.

---

## Regular Expressions

Regular expressions (regex) are patterns used to match and validate strings, especially user input.

### Common Syntax

| Symbol   | Meaning                        |
|----------|--------------------------------|
| `.`      | Any single character           |
| `*`      | Zero or more                   |
| `+`      | One or more                    |
| `?`      | Zero or one                    |
| `{n}`    | Exactly n times                |
| `{n,m}`  | Between n and m times          |
| `\`      | Escape special characters      |

**Summary:**  
Regex is a powerful tool for pattern matching and input validation. It’s widely used in form handling and data parsing.

---

## CSS Fundamentals

CSS (Cascading Style Sheets) controls the visual presentation of HTML elements.

### Example

```css
div {
  height: 420px;
  background-color: lightblue;
}
```

- CSS uses key-value pairs for styling.
- Styles can be inline, internal, or external.

**Summary:**  
CSS separates content from design, allowing flexible and consistent styling across web pages.

---

## JavaScript Essentials

JavaScript enables interactivity and dynamic behavior in web pages.

### Event Listeners

```javascript
input.addEventListener("keyup", function(event) {
  for (let word of WORDS) {
    if (word.startsWith(input.value)) {
      html += `<li>${word}</li>`;
    }
  }
});
```

### Common Events

- `submit`, `click`, `keyup`, `keydown`, `focus`, `blur`, `change`, `drag`, `load`, `unload`, `mouseover`, `mousedown`, `mouseup`

**Summary:**  
JavaScript brings web pages to life by responding to user actions and manipulating the DOM. Event listeners are key to building interactive interfaces.

---

## Next Topics to Study

To deepen your understanding of web and network technologies, consider exploring:

- Browser rendering engines and performance optimization
- WebSockets and real-time communication
- RESTful APIs and GraphQL
- Content Delivery Networks (CDNs)
- TLS/SSL and certificate management
- Responsive design and media queries
- JavaScript frameworks (e.g. React, Vue, Angular)
- Web accessibility standards (WCAG)
- Network security and firewalls
