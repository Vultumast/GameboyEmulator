using EmulatorGUI.EmulatorLib;

namespace EmulatorGUI.Tests;

public class ExtensionMethodTests
{
    [Fact]
    public void ToString_WithValidOperandType_ReturnsNonEmptyString()
    {
        // Arrange
        OperandType value = OperandType.RegisterB;

        // Act
        string result = ExtensionMethods.ToString(value);

        // Assert
        Assert.NotNull(result);
        Assert.NotEqual("", result);
    }

    [Fact]
    public void ToString_WithNoneOperandType_ReturnsEmptyString()
    {
        // Arrange
        OperandType value = OperandType.None;

        // Act
        string result = ExtensionMethods.ToString(value);

        // Assert
        Assert.NotNull(result);
        Assert.Equal("", result);
    }

    [Fact]
    public void ToString_WithInvalidOperandType_ReturnsEmptyString()
    {
        // Arrange
        OperandType value = (OperandType)(-1);

        // Act
        string result = ExtensionMethods.ToString(value);

        // Assert
        Assert.NotNull(result);
        Assert.Equal("", result);
    }
}