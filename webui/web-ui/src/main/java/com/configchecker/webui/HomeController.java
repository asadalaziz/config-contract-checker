package com.configchecker.webui;

import org.springframework.stereotype.Controller;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.PostMapping;
import org.springframework.web.bind.annotation.RequestParam;
import org.springframework.web.multipart.MultipartFile;

import com.fasterxml.jackson.databind.JsonNode;
import com.fasterxml.jackson.databind.ObjectMapper;
import java.util.ArrayList;
import java.util.List;


import org.springframework.ui.Model;
import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.io.File;
import java.io.IOException;

@Controller
public class HomeController {

    @GetMapping("/")
    public String home() {
        return "index";
    }

    @PostMapping("/validate")
    public String validate(
        @RequestParam("configFile") MultipartFile configFile,
        @RequestParam("contractFile") MultipartFile contractFile,
        Model model
    ) throws IOException, InterruptedException {

    // 1. Create uploads directory
    String baseDir = System.getProperty("user.dir");
    File uploadDir = new File(baseDir, "uploads");

    if (!uploadDir.exists()) {
        uploadDir.mkdirs();   // <-- IMPORTANT
    }


    // 2. Save uploaded files
    File config = new File(uploadDir, "config.txt");
    File contract = new File(uploadDir, "contract.txt");

    configFile.transferTo(config);
    contractFile.transferTo(contract);

    // 3. Call checker.exe
    ProcessBuilder builder = new ProcessBuilder(
            "..\\..\\checker.exe",
            config.getAbsolutePath(),
            contract.getAbsolutePath()
    );

    builder.redirectErrorStream(true);
    Process process = builder.start();

    // 4. Read output (JSON)
    BufferedReader reader = new BufferedReader(
        new InputStreamReader(process.getInputStream())
    );

    StringBuilder output = new StringBuilder();
    String line;
    while ((line = reader.readLine()) != null) {
        output.append(line).append("\n");
    }

    // Parse JSON
    ObjectMapper mapper = new ObjectMapper();
    JsonNode root = mapper.readTree(output.toString());

    List<ViolationDTO> violations = new ArrayList<>();

    JsonNode vNode = root.get("violations");
    if (vNode != null && vNode.isArray()) {
        for (JsonNode node : vNode) {
            violations.add(new ViolationDTO(node.get("message").asText()));
        }
    }

    // Send to UI
    model.addAttribute("violations", violations);
    model.addAttribute("hasViolations", !violations.isEmpty());
    return "index";
}
}
