#include <iostream>
#include <thread>
#include <chrono>
#include <memory>

#include <GLFW/glfw3.h>
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

#include "WindowsMonitor.h"


int main() {
    // GLFW window
    if (!glfwInit()) {
        std::cerr << "Nie udalo sie zainicjowac GLFW!\n";
        return -1;
    }

    GLFWwindow* window = glfwCreateWindow(800, 600, "Monitor Systemu C++", nullptr, nullptr);
    if (!window) {
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);

    // imgui initialization
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    ImGui::StyleColorsDark(); 

    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 130");

    std::unique_ptr<ISystemMonitor> monitor = std::make_unique<WindowsMonitor>();
    double lastTime = 0.0;


    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        double currentTime = glfwGetTime();
        if (currentTime - lastTime >= 1.0) {
            monitor->update();
            lastTime = currentTime;
        }

        ImGui::Begin("Parametry Komputera", nullptr, ImGuiWindowFlags_AlwaysAutoResize);
        ImGui::Text("Zuzycie procesora (CPU):");

        float cpu = static_cast<float>(monitor->getCpuUsage());
        std::string cpuText = std::to_string((int)cpu) + "%";
        ImGui::ProgressBar(cpu / 100.0f, ImVec2(0.0f, 0.0f), cpuText.c_str()); 

        ImGui::Spacing();
        
        ImGui::Text("Zuzycie pamieci (RAM):");

        float usedRam = static_cast<float>(monitor->getRamUsage());
        float totalRam = static_cast<float>(monitor->getTotalRam());
        float ramUsage = totalRam > 0 ? (usedRam / totalRam) : 0.0f;
        std::string ramText = std::to_string((int)usedRam) + "/" + std::to_string((int)totalRam);
        ImGui::ProgressBar(ramUsage, ImVec2(0.0f, 0.0f), ramText.c_str());

        ImGui::End();

        ImGui::Render();
        int display_w, display_h;
        glfwGetFramebufferSize(window, &display_w, &display_h);
        glViewport(0, 0, display_w, display_h);
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f); 
        glClear(GL_COLOR_BUFFER_BIT);
        
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        glfwSwapBuffers(window);
    }


    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
    glfwDestroyWindow(window);
    glfwTerminate();



    // while (true) {
    //     monitor->update();

    //     std::cout << "CPU: " << monitor->getCpuUsage() << "%\n";
    //     std::cout << "RAM: " << monitor->getRamUsage() << "MB / "
    //         << monitor->getTotalRam() << "MB\n";


    //     std::this_thread::sleep_for(std::chrono::seconds(1));
    // }

    return 0;
}