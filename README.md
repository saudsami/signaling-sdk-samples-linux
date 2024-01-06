# Agora Signaling SDK for Linux C++ reference app

This repository holds the code examples used for the [Agora Signaling SDK for Linux C++](https://docs-beta.agora.io/en/signaling/overview/product-overview?platform=linux-cpp) documentation. Clone the repo, run and test the samples, use the code in your own project. Enjoy.

- [Samples](#samples)
- [Prerequisites](#prerequisites)
- [Run this project](#run-this-project)
- [Contact](#contact)

**This reference app uses Signaling SDK v2.x**.

## Samples  

The runnable code examples are:

- [SDK quickstart](./README.md) - the minimum code you need to integrate low-latency, high-concurrency
  signaling features into your app using Signaling SDK.
- [Secure authentication with tokens](./README.md) - quickly set up an authentication token server, retrieve a token from the server, and use it to connect securely to Signaling as a specific user.
- [Stream channels](./README.md) - communicate to other users in topics.
- [Store channel and user data](./README.md) - easily store data for users and channels without the need to
  set up your own databases. 
- [Connect through restricted networks with Cloud Proxy](./README.md) - ensure reliable connectivity for your users when they connect from an
  environment with a restricted network.
- [Data encryption](./README.md) - integrate built-in data encryption into your app using Signaling.
- [Geofencing](./README.md) - only connect to Signaling within the specified region.

## Prerequisites

Before getting started with this reference app, ensure you have the following set up:

- Linux
- C++

## Run this project

To run the sample projects in this folder, take the following steps:

1. **Clone the repository**

    To clone the repository to your local machine, open Terminal and navigate to the directory where you want to clone the repository. Then, use the following command:

    ```bash
    git clone https://github.com/saudsami/signaling-sdk-samples-linux.git
    ```

1. **Integrate the Signaling SDK for Linux** 

    1. Download the [Agora Signaling SDK 2.x for Linux](https://download.agora.io/rtm2/release/Agora_RTM_C%2B%2B_SDK_for_Linux_v218.zip?_gl=1)

    2. Unzip the contents to a folder `<samples-root>`.

    3. Copy the file `libagora_rtm_sdk.so` to the `<samples-root>/lib` folder.

    4. Copy the `include` folder to `<samples-root>`.
   
1. **Modify the project configuration**

   This app loads connection parameters from a configuration file [`config.json`](./config.json).  If a valid `serverUrl` is provided, all samples use the token server to obtain a token, except the **SDK quickstart**  which uses `token`.

   Ensure that `config.json` is populated with the required parameter values before running this reference app.

    - `uid`: The user ID associated with the application.
    - `appId`: (Required) The unique ID for the application obtained from [Agora Console](https://console.agora.io). 
    - `channelName`: The default name of the channel to join.
    - `token`:An token generated for `channelName`. You generate a temporary token using the [Agora token builder](https://agora-token-generator-demo.vercel.app/).
    - `serverUrl`: The URL for the token generator. See [Secure authentication with tokens](https://docs-beta.agora.io/en/signaling/get-started/authentication-workflow) for information on how to set up a token server.
    - `tokenExpiryTime`: The time in seconds after which a token expires.

1. **Build and run the project**

   In the project folder, open Terminal and run the following command:

    ``` bash
    sh +x clean_build.sh
    ```

1. **Run the samples in the reference app**

   To run the reference app, execute the following command in the terminal:

   ```shell
   ./build/RTMQuickStart
   ```

## Contact

If you have any questions, issues, or suggestions, please file an issue in our [GitHub Issue Tracker](https://github.com/AgoraIO/signaling-sdk-samples-linux/issues).
