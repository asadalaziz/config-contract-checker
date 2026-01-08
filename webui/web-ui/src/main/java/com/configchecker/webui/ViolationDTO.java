package com.configchecker.webui;

public class ViolationDTO {
    private String message;

    public ViolationDTO() {}
    public ViolationDTO(String message) { this.message = message; }

    public String getMessage() { return message; }
    public void setMessage(String message) { this.message = message; }
}
