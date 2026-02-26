pipeline {
    agent any
    stages {
        stage('Build Backend Image') {
            steps {
                sh '''
                docker rmi -f backend-app || true
                # REMOVED CC_LAB-6/ prefix
                docker build -t backend-app backend
                '''
            }
        }
        stage('Deploy Backend Containers') {
            steps {
                sh '''
                docker network create app-network || true
                docker rm -f backend1 backend2 || true
                docker run -d --name backend1 --network app-network backend-app
                docker run -d --name backend2 --network app-network backend-app
                '''
            }
        }
        stage('Deploy NGINX Load Balancer') {
            steps {
                sh '''
                # 1. Build the NGINX image using the Dockerfile in your nginx folder
                docker build -t custom-nginx nginx
                
                # 2. Clean up and run
                docker rm -f nginx-lb || true
                docker run -d \
                  --name nginx-lb \
                  --network app-network \
                  -p 80:80 \
                  custom-nginx
                '''
            }
        }
    }
    post {
        success {
            echo 'Pipeline executed successfully. NGINX load balancer is running.'
        }
        failure {
            echo 'Pipeline failed. Check console logs for errors.'
        }
    }
}
