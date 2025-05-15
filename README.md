# mte241 tutorials

To see slides, do

```bash
cd tut/
python -m http.server 8080
```

Then you can view it on `http://localhost:8080/`

You can change the following code in the `index.html` to see slides for different weeks.

```bash
var slideshow = remark.create({
    sourceUrl: 'week2.md',
    ratio: '16:9'          // widescreen format similar to PowerPoint
});
```

- Press `F` to enter fullscreen mode
- Press `P` to enter presenter mode
- Press `H` to see all slide show commands

---

My goal is to make the .md file more readable. However, code snippets used for slide formatting are inevitably included, and they can be mostly ignored when reading the file. Here is a summary:

- `.invisible-slide-comment`: content that will not show up in slides
- `<div>`, `.align-left`, and `.align-right`: slide layout related
- `???`: This syntax is used for slide shows and can be ignored in the markdown source. It indicates that any content following `???` until the next `---` is visible only in presenter mode.

---

Huanyi Chen
h365chen@uwaterloo.ca
