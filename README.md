# C++ Project with Docker Support

This is a C++ project that uses Docker for a server component and requires a few dependencies for building and running.

## Requirements

### System Requirements:
- **Linux** (or WSL on Windows)
- **Curl** (for HTTP requests and interactions with the server)

### Dependencies:
- **nlohmann JSON** library: A header-only library for working with JSON. You can install it via a package manager or manually.
  - On Ubuntu/Debian-based systems:  
    ```bash
    sudo apt-get install nlohmann-json3-dev
    ```

- **Docker** (optional, for running the Docker server):
  - Install Docker from the official Docker website or use your system's package manager.
  - Docker is needed to run the server component if you're using the `docker-server` directory.

### Installation:

1. **Clone the Repository:**
    ```bash
    git clone https://gitlab.com/your-username/your-project.git
    cd your-project
    ```

2. **Install Dependencies:**
   - For **nlohmann JSON**, if not installed system-wide, you can download it or install via package manager.
   - For **curl**, install it via your package manager:
     ```bash
     sudo apt-get install curl
     ```

3. **Build the Project:**
   - Navigate to the root directory of the project and run the Makefile:
     ```bash
     make
     ```

4. **(Optional) Run the Docker Server:**
   - If you want to run the Docker server, you can build and run the Docker container:
     ```bash
     cd docker-server
     docker build -t request-logger .
     docker run -p 5000:5000 request-logger
     ```
   - This will start the Docker server on port 5000. You can modify these settings based on your requirements.

### Usage:

1. **Running the Application:**
   - After building, you can run the application by executing the output binary in `bin/` (or wherever your Makefile places it).
     ```bash
     ./bin/parking-system
     ```



