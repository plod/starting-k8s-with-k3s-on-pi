#!/bin/bash
# Get current projectID
export PROJECTID=$(gcloud config get-value core/project 2>/dev/null)

# Create a service account
gcloud iam service-accounts create inlets \
--description "inlets-operator service account" \
--display-name "inlets"

# Get service account email
export SERVICEACCOUNT=$(gcloud iam service-accounts list | grep inlets | awk '{print $2}')

# Assign appropriate roles to inlets service account
gcloud projects add-iam-policy-binding $PROJECTID \
--member serviceAccount:$SERVICEACCOUNT \
--role roles/compute.admin

gcloud projects add-iam-policy-binding $PROJECTID \
--member serviceAccount:$SERVICEACCOUNT \
--role roles/iam.serviceAccountUser

# # Create inlets service account key file
gcloud iam service-accounts keys create key.json \
--iam-account $SERVICEACCOUNT

# # Create a secret to store the service account key file
kubectl create secret generic inlets-access-key --from-file=inlets-access-key=key.json

# # Add and update the inlets-operator helm repo
helm repo add inlets https://inlets.github.io/inlets-operator/

helm repo update

# # Install inlets-operator with the required fields
helm upgrade inlets-operator --install inlets/inlets-operator \
  --set provider=gce,zone=europe-west2-c,projectID=$PROJECTID