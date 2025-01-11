const colorInput = document.getElementById('colorInput');
const colorDisplay = document.getElementById('colorDisplay');
const colorValue = document.getElementById('colorValue');

// Update the color display and text when the color input changes
colorInput.addEventListener('input', (event) => {
    const selectedColor = event.target.value;
    colorDisplay.style.backgroundColor = selectedColor;
    colorValue.textContent = `Selected Color: ${selectedColor}`;
}); 