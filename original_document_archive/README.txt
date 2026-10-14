Original course documents and images

This archive inventories all 54 supplied PDF, DOCX, PNG, JPG, and JPEG files in
the laboratory course source directory. It retains 50 source items: 37 current
lecture PDFs already preserved elsewhere in this repository and 13 added files
here: three historical course exam DOCX files, seven exam screenshots, two
Lab 1.1 screenshots, and one assignment index. Three lab-exemption / waiver
exam rule PDFs are explicitly excluded at the user's request. The earlier
2021 Lab13 1745 edition is excluded as superseded by 2015_update.

Original exam statements, parameters, diagrams, schedules, and anonymous
historical grades are preserved. Archival judge results are historical
learning material and do not establish correctness of the current solutions.
The assignment index has no visible student identity and is retained intact.
Student login numbers, names in IDE filenames, personal file paths, and
document author metadata are replaced by random aliases. Identifying screenshot
pixels are removed from the actual image. The published PNG derivatives have
no EXIF, hidden original images, or identifying metadata. Their decoded pixels
are unchanged outside the documented privacy rectangles.

The two exam prompt DOCX files retain every package member byte-exact except
the author metadata in docProps/core.xml. The results screenshot DOCX also
replaces its identifying image with a privacy-edited derivative of the same
dimensions. Document XML, styles, relationship targets, footnotes, endnotes,
and image placement geometry remain byte-exact in all three DOCX files.
All full embedded images and all XML story text were inspected.

The canonical render_docx.py was attempted but could not run because the
bundled Windows runtime lacks LibreOffice soffice.exe. Actual fallback QA used
hidden Microsoft Word COM with macros disabled and read-only Open, exported
private PDFs, and rasterized pages with Poppler. The three DOCX files rendered
to 9, 18, and 1 pages; all 28 published pages were visually reviewed. Source
and published exports have identical native text and identical rendered pixels
outside the declared privacy region. All six source/published DOCX input files
remained byte-identical during rendering. This records the successful Word
fallback separately from the unavailable canonical LibreOffice renderer.

The original files in the local source collection were not changed. Original
and published SHA-256 hashes are listed in manifest.json; private filename and
identity mappings are not published. All 54 supplied document/image items are
accounted for. All three supplied lab-exemption editions (2023-09-05,
2024-03-05, and 2025-03-04) are omitted from the current tree by explicit user
request, not counted as missing files. Different lab topics, Reviews, debugger
guides, course years, and ordinary historical midterm/final exam statements
remain preserved. Code, headers, data, IDE files, and the contents of provided
program archives are handled by the separate source archive.

Run from the repository root:
    python original_document_archive/check_archive.py
