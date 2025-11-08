# Overleaf Upload Instructions

## Problem: Images Not Appearing
The LaTeX report has been updated to use correct paths: `results/plots/time_loglog.png` and `results/plots/ops.png`

## Option 1: Upload Complete Zip File ✅ (Recommended)
1. Use the generated `AOA_Project_Overleaf.zip` file on your desktop
2. On Overleaf: New Project → Upload Project → Select the zip file
3. Overleaf will preserve the folder structure automatically
4. Compile `report/main.tex` - images should appear correctly

## Option 2: Manual Upload (Alternative)
If zip upload doesn't work:

1. Create new Overleaf project
2. Upload `report/main.tex` as your main document
3. Create folders in Overleaf:
   - Right-click → Create folder → `results`
   - Inside `results` → Create folder → `plots`
4. Upload images to the correct folders:
   - Upload `time_loglog.png` to `results/plots/`
   - Upload `ops.png` to `results/plots/`
5. Upload other files:
   - `src/main.cpp` to `src/` folder
   - `README.md`, `requirements.txt` to root

## Option 3: Simple Image Paths (Quick Fix)
If you want images in the same folder as main.tex:

1. Copy both PNG files to the `report/` folder
2. In Overleaf, edit main.tex and change:
   ```latex
   \includegraphics[width=0.45\textwidth]{results/plots/time_loglog.png}
   \includegraphics[width=0.45\textwidth]{results/plots/ops.png}
   ```
   to:
   ```latex
   \includegraphics[width=0.45\textwidth]{time_loglog.png}  
   \includegraphics[width=0.45\textwidth]{ops.png}
   ```

## Troubleshooting
- If images still don't show: Check the file names are exactly `time_loglog.png` and `ops.png`
- If compilation errors: Make sure you have the algorithm package (should work with standard Overleaf templates)
- If path issues persist: Use Option 3 (simple paths) as backup

The zip file `AOA_Project_Overleaf.zip` is ready for direct upload to Overleaf!