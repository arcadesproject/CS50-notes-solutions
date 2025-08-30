# WAV Volume Modifier – Explanation

### **What it does**

* Takes a `.wav` file as input.
* Multiplies each audio sample by a **volume factor** (e.g. `2.0` doubles loudness, `0.5` halves it).
* Writes the result to a new `.wav` file.
* Copies the **header** so the output stays a valid WAV file.

---

### **Step-by-step**

1. **Argument check**
   Program requires exactly 3 arguments:

   ```
   ./volume input.wav output.wav factor
   ```

2. **File handling**

   * `fopen(argv[1], "rb")` → open input file in **binary read mode**.
   * `fopen(argv[2], "wb")` → open output file in **binary write mode**.
   * `"rb"/"wb"` is crucial on Windows (prevents `\n` translation).
   * r and w for text files (txt, csv) on windows so convertes \r\n to \n (\r is carriage return)

3. **Volume factor**

   * `factor = atof(argv[3])` → convert string to floating-point.
   * Used to scale each audio sample.

4. **Copy and validate header**

   * Allocate `uint8_t header[HEADER_SIZE];`.
   * `fread` 44 bytes into `header`.
   * Validate WAV signature:

     * Bytes `0–3` must be `"RIFF"`.
     * Bytes `8–11` must be `"WAVE"`.
   * Write header unchanged to output file.
   * **Note:** `uint8_t` = *unsigned* 8-bit integer (0–255), ideal for raw bytes.

5. **Process samples**

   * Use `int16_t buffer;` to read 16-bit PCM audio samples.
   * Multiply each sample by `factor`.
   * Write modified value to output file.
   * **Note:** `int16_t` = *signed* 16-bit integer (−32,768 → 32,767).
     Audio samples can be positive (sound wave crest) or negative (trough).

6. **Close files**

   * `fclose(input);` and `fclose(output);` to free resources.

---

### **Key things to remember**

* **Header first:** Always copy the 44-byte header unchanged, otherwise the output isn’t a valid WAV file.
* **Correct types:**

  * `uint8_t` for header (raw bytes, unsigned).
  * `int16_t` for samples (signed audio data).
* **Beware clipping:** Scaling with `factor > 1` can exceed the `int16_t` range, causing distortion.
* **Binary mode:** Use `"rb"` and `"wb"` when dealing with WAV (or any binary format).
* **Robust code:** Check `fread`/`fwrite` return values to handle partial reads/writes safely.
* **Portability:** This approach assumes **16-bit PCM WAV files with 44-byte headers**. More complex WAVs may include extra chunks.

---

Would you like me to also add a **diagram of the 44-byte WAV header layout** into this explanation, so you can visually see where `"RIFF"` and `"WAVE"` live inside?
